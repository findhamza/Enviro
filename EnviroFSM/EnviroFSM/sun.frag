#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec4 ourPos;
  
void main()
{
    FragColor = vec4(ourColor.x, abs(ourPos.y+1), -abs(ourPos.x), 0.5);
}