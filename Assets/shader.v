#version 420 core
//#extension ARB_enhanced_layouts : require

layout(location = 0) 
in vec4 pos;
//layout(location = 1)
in vec2 uv;

//Instance
layout(location = 2)
in mat4 world;


layout( std140, binding = 0 ) uniform VertexBlock
{
	mat4 view;
	mat4 proj;
};


out vec2 texCoord;

void main()
{
	texCoord = uv ;
	mat4  pvw =  proj * view * world;
	gl_Position =   pvw * pos;

}