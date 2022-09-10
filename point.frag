#version 460 core
in vec4 vertexColor;
out vec4 fragment;
void main()
{
	//fragment = vec4(1.0, 0.0, 0.0, 1.0);
	fragment = vertexColor;
}