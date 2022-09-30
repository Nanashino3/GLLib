#version 460 core

in vec2 fragTexCoord;
out vec4 outColor;
uniform sampler2D uTexture;

void main()
{
	outColor = texture(uTexture, fragTexCoord);
}