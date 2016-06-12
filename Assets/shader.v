#version 420 core
//#extension ARB_enhanced_layouts : require

layout(location = 0) 
in vec4 pos;
//layout(location = 1)
in vec2 uv;


layout( std140, binding = 0 ) uniform VertexBlock
{
	mat4 wvp;
};


out vec2 texCoord;

void main()
{
	texCoord = uv ;
	gl_Position =   wvp * pos;

}