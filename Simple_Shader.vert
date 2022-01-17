#version 450

vec2 positions[3] = vec2[](vec2(0.0,-0.5)/*top middle*/,vec2(0.5,0.5)/*bottom right*/,vec2(-0.5,0.5)/*bottom left*/);//tri is drawn clockwise and (0,0) is ther centre of the screen

void main()
{
	gl_Position = vec4(positions[gl_VertexIndex],0.0,1.0);
}