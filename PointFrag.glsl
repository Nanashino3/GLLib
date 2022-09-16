#version 460 core
in vec4 vertexColor;
out vec4 fragment;
void main()
{
	fragment = vertexColor;
}