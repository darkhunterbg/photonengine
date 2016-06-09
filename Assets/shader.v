#version 420 core
#extension ARB_enhanced_layouts : require

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 uv;

out vec2 texCoord;

void main()
{
	texCoord = uv * vec2(1,-1);
	gl_Position = pos;

}