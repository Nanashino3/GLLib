#version 460 core

uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;
out vec2 fragTexCoord;

void main()
{
	vec4 pos = vec4(inPosition, 1.0f);
	gl_Position = uWorldTransform * uViewProjection * pos;
	fragTexCoord = inTexCoord;
}