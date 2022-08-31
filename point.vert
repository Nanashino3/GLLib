#version 460 core
uniform mat4 worldTransform;
uniform mat4 viewProjection;
layout( location = 0 ) in vec3 inPosition;
//layout( location = 1 ) in vec2 inTexCoord;
//out vec2 fragTexCoord;
void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * worldTransform * viewProjection;
	//fragTexCoord = inTexCoord;
}