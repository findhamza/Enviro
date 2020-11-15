#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec4 ourPos;
  
void main()
{
    FragColor = vec4(ourColor.x+ourPos.y-ourColor.y+.2, ourColor.y+ourPos.y-ourColor.z+.2, ourColor.z+ourPos.y-ourColor.y+.2, 0.5);
}