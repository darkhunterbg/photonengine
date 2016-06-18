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
	mat4 vp;
};


out vec2 texCoord;

void main()
{
	texCoord = uv ;
	mat4  wvp =  vp;
	gl_Position =   wvp  * pos ;

}