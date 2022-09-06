#version 460 core
uniform mat4 viewProjection;
uniform mat4 worldTransform;
layout( location = 0 ) in vec3 inPosition;
void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * worldTransform * viewProjection;
}