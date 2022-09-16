#version 460 core
uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;
in vec4 inPosition;
in vec4 inNormal;
out vec4 vertexColor;

void main()
{
	vertexColor = inNormal;
	gl_Position = uViewProjection * uWorldTransform * inPosition;
}