#version 420 core



//outputs to frame buffer 0
layout(location = 0) out vec4 colorBuffer;

in vec2 uv;

//structure, aligned by vec4, starts at location 0
layout( std140, binding = 1 ) uniform FragmentBlock
{
 vec4 color;
};
 uniform sampler2D texSampler;

void main()
{
	vec3 texColor = texture(texSampler, uv).rgb;
	colorBuffer = color;
	colorBuffer.rgb =  texColor;//* gl_FragCoord.w;
	
}