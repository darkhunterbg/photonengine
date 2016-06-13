#version 420 core


layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

//outputs to frame buffer 0


 in vec2 texCoord[3];
 
out vec2 uv;



void main()
{
	for(int i = 0; i < gl_in.length(); i++)
	{
		// copy attributes
		gl_Position = gl_in[i].gl_Position;
		
		if(texCoord[i].x == 0 && texCoord[i].y == 0)
		{
			//gl_Position = vec4(0,0,0,1);
		}
		uv = texCoord[i];
 
		// done with the vertex
		EmitVertex();

	}
		EndPrimitive();
}