#version 460 core
uniform mat4 modelView;
uniform mat4 projection;
in vec4 inPosition;
void main()
{
	gl_Position = projection * modelView * inPosition;
}