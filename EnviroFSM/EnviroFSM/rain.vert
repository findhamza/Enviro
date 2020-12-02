#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec4 ParticleColor;

uniform vec2 offset;
uniform vec4 color;

void main()
{
    float scale = 10.0f;
    ParticleColor = color;
    gl_Position = vec4((vertex.xy * scale) + offset, 0.0, 1.0);
}