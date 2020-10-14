#include "EnviroEngine.h"

EnviroEngine* EnviroEngine::instance = 0;

bool EnviroEngine::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	// glfw: initialize and configure
	// ------------------------------
	//Icons made by Freepik from www.flaticon.com
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);


	// glfw window creation
	// --------------------
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	// build and compile our shader program
// ------------------------------------
	//Shader Loader
	mainShader = Shader("shader.vert", "shader.frag");

	//Antialiasing
	glEnable(GL_MULTISAMPLE);

	do {
		plantA.plantInput(randomBool(), randomBool(), 5);
	} while (plantA.getTestState());

	sun.generateRim(); sun.generateSunVertices(); sun.generateSunIndices();

	std::vector<Vertex> plantVert = plantA.getPlantVertex();
	std::vector<unsigned int> plantInds = plantA.getPlantUIndices();
	plantObject = Mesh(plantVert,plantInds);

	return true;
}

bool EnviroEngine::running()
{
	return !glfwWindowShouldClose(window);
}

void EnviroEngine::handleEvents()
{
	processInput(window);
}

void EnviroEngine::update()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------

	//plantA.plantInput(randomBool(), randomBool(), 5);
	plantA.drawTree();
	std::vector<float> plantVerts = plantA.getPlantVertices();
	std::vector<int> plantInds = plantA.getPlantIndices();
	sun.updateSun();
	std::vector<float> sunVerts = sun.getSunVertices();
	std::vector<int> sunInds = sun.getSunIndices();


	std::vector<float> vertices;
	vertices.reserve(plantVerts.size() + sunVerts.size());
	vertices.insert(vertices.end(), plantVerts.begin(), plantVerts.end());
	vertices.insert(vertices.end(), sunVerts.begin(), sunVerts.end());

	std::vector<int> indices;
	indices.reserve(plantInds.size() + sunInds.size());
	indices.insert(indices.end(), plantInds.begin(), plantInds.end());
	indices.insert(indices.end(), sunInds.begin(), sunInds.end());



	indicesCount = plantInds.size();

	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, plantVerts.size() /*jee*/ , plantVerts.data(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, /*plantVerts.size()*/ jee, plantVerts.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, plantInds.size() /*jee/6*/, plantInds.data(), GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, /*plantInds.size()*/ jee/6, plantInds.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);	

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void EnviroEngine::render()
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //werid teal color
	glClearColor(0.490f, 0.752f, 0.968f, 1.0f); //malibu blue
	glClear(GL_COLOR_BUFFER_BIT);
	// draw our first triangle
	//glUseProgram(shaderProgram);
	mainShader.use();
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glPointSize(3);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // no need to unbind it every time 

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &EBO);

}

void EnviroEngine::clean()
{
	quit();
}

void EnviroEngine::quit()
{
	glfwTerminate();
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

std::string getShader(std::string fileName)
{
	std::ifstream infileVert(fileName, std::fstream::in);
	std::string ShaderContent;
	if (infileVert.is_open())
		ShaderContent = std::string(std::istreambuf_iterator<char>(infileVert),
			std::istreambuf_iterator<char>());

	return ShaderContent;
}

float randomFloat() {
	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_real_distribution<>(0, 1), rndEngine);
	return gen();
}

bool randomBool() {
	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), rndEngine);
	return gen();
}