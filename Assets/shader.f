#version 330 core
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_explicit_attrib_location : enable
#extension GL_ARB_enhanced_layouts : enable
#extension GL_ARB_separate_shader_objects : enable

//outputs to frame buffer 0
layout(location = 0) out vec4 output;

//structure, aligned by vec4, starts at location 0
layout( location = 0, std140 ) uniform Block
{
 vec4 color;
};

void main()
{
  output = color;
}