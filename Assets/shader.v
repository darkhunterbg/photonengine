#version 420 core

struct vertex
{
	vec4 pos;
	vec2 texCoord;
};

out vec2 texCoord;

layout(location = 0) in vertex v;

void main()
{
	texCoord = v.texCoord;
	gl_Position = v.pos;

}