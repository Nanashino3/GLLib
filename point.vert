#version 460 core
uniform mat4 modelView;
uniform mat4 projection;
in vec4 inPosition;
in vec4 inColor;
out vec4 vertexColor;
void main()
{
	vertexColor = inColor;
	gl_Position = projection * modelView * inPosition;
}