#version 330 core

layout(location = 0) in vec4 vertexPosition;

void main()
{
	gl_Position = vertexPosition;
}