#version 330 core
in vec4 ParticleColor;
out vec4 color;

void main()
{
    color = vec4(ParticleColor.x-0.7, ParticleColor.y-0.7, ParticleColor.z+0.7, ParticleColor.a);
}  