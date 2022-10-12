#version 460 core
uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec4 inNormal;
out vec4 vertexColor;

void main()
{
	vertexColor = inNormal;
	gl_Position = uViewProjection * uWorldTransform * inPosition;
}