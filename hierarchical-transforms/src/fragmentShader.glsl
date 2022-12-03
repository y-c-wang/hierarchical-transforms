#version 330 core

out vec4 FragColor; 

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture0;
uniform bool textured;
  
void main()
{
	if(textured)
	{
		FragColor = texture(texture0, TexCoord);
	}
	else
	{
		FragColor = vec4(ourColor, 1.0);
	}
}
