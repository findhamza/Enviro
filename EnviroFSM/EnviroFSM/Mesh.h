#ifndef MESH_H
#define MESH_H

#include "syslib.h"
#include "graphics.h"
#include "Shader.h"

using namespace std;

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    unsigned int VAO;
    unsigned int id;

    // constructor
    Mesh()
    {
        VAO = 0;
        VBO = 0;
        EBO = 0;
    }
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, unsigned int id)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->id = id;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    void Update(vector<Vertex> vertices, vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    void UpdateInds(vector<unsigned int> indices)
    {
        this->indices = indices;

        rebindBufferIndices();
    }

    // render the mesh
    void Draw(Shader& shader)
    {
        //start shader
        shader.use();
        // draw mesh
        glBindVertexArray(VAO);
        //glPointSize(2);
        //glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    //
    //
    //Nest Particle Class
    class ParticleGenerator {

    public:

        ParticleGenerator(){}

        ParticleGenerator(Shader shader, unsigned int amount)
            : shader(shader), amount(amount)
        {
            this->init();
        }

        void Update(float dt, unsigned int newParticles, glm::vec2 offset)
        {

            // add new particles 
            for (unsigned int i = 0; i < newParticles; ++i)
            {
                int unusedParticle = this->firstUnusedParticle();
                this->respawnParticle(this->particles[unusedParticle], offset);
            }
            // update all particles
            for (unsigned int i = 0; i < this->amount; ++i)
            {
                Particle& p = this->particles[i];
                p.Life -= dt; // reduce life
                if (p.Life > 0.0f)
                {	// particle is alive, thus update
                    p.Position -= p.Velocity * dt;
                    p.Color.a -= dt * 2.5f;
                }
            }
        }

        void Draw()
        {
            // use additive blending to give it a 'glow' effect
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            this->shader.use();
            for (Particle particle : this->particles)
            {
                if (particle.Life > 0.0f)
                {
                    this->shader.setVec2("offset", particle.Position);
                    this->shader.setVec4("color", particle.Color);
                    glBindVertexArray(this->VAO);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                    glBindVertexArray(0);
                }
            }
            // don't forget to reset to default blending mode
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

    private:

        vector<Particle> particles;
        unsigned int amount, VAO;
        Shader shader;

        void init()
        {
            // set up mesh and attribute properties
            unsigned int VBO;
            float particle_quad[] = {
                0.0f, 0.001f, 0.0f, 0.001f,
                0.001f, 0.0f, 0.001f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,

                0.0f, 0.001f, 0.0f, 0.001f,
                0.001f, 0.001f, 0.01f, 0.001f,
                0.001f, 0.0f, 0.001f, 0.0f
            };
            glGenVertexArrays(1, &this->VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(this->VAO);
            // fill mesh buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
            // set mesh attributes
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glBindVertexArray(0);

            // create this->amount default particle instances
            for (unsigned int i = 0; i < this->amount; ++i)
                this->particles.push_back(Particle());
        }

        unsigned int lastUsedParticle = 0;
        unsigned int firstUnusedParticle()
        {
            // first search from last used particle, this will usually return almost instantly
            for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
                if (this->particles[i].Life <= 0.0f) {
                    lastUsedParticle = i;
                    return i;
                }
            }
            // otherwise, do a linear search
            for (unsigned int i = 0; i < lastUsedParticle; ++i) {
                if (this->particles[i].Life <= 0.0f) {
                    lastUsedParticle = i;
                    return i;
                }
            }
            lastUsedParticle = 0;
            return 0;
        }

        void respawnParticle(Particle& particle, glm::vec2 offset)
        {
            float random = ((rand() % 101) + (-50)) / 100.0f;
            float randVelocity = ((float(rand()) / float(RAND_MAX)) * (1.0f - 0.4f)) + 0.4f;
            float rColor = 0.5f + ((rand() % 100) / 100.0f);
            particle.Position = glm::vec2((random*0.72f)-0.05f, 0.45f);// random + offset;
            particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
            particle.Life = 200.0f;
            particle.Velocity = glm::vec2(randVelocity*random*-0.02, 0.1f*(randVelocity));
        }
    };

private:
    // render data 
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(id, &VAO);
        glGenBuffers(id, &VBO);
        glGenBuffers(id, &EBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW); //looks really beautiful but creates reflections
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_DYNAMIC_DRAW); //similar to old code (-1 to stop draw glitch.)

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex Colors
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
        glBindVertexArray(0);
    }

    void rebindBufferIndices()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW); //looks really beautiful but creates reflections
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_DYNAMIC_DRAW); //similar to old code (-1 to stop draw glitch.)
    }

};
#endif