#version 420 core



//outputs to frame buffer 0
layout(location = 0) out vec4 colorBuffer;

in vec2 texCoord;

//structure, aligned by vec4, starts at location 0
layout( std140, binding = 0 ) uniform Block
{
 vec4 color;
};
 uniform sampler2D texSampler;

void main()
{
	vec3 texColor = texture(texSampler, texCoord).rgb;
	//colorBuffer = color;
	colorBuffer.rgb= texColor;
	//colorBuffer.rg= texCoord;
	colorBuffer.a = 1;
}