#version 460 core
uniform mat4 uWorldTransform;	// ���[���h�ϊ����W
uniform mat4 uViewProjection;	// �r���[�ˉe�s��

layout (location = 0) in vec3 inPosition;	// �ʒu���W
layout (location = 1) in vec3 inNormal;		// �@�����W
layout (location = 2) in vec2 inTexCoord;	// UV���W

out vec3 fragNormal;
out vec2 fragTexCoord;

void main()
{
	// w������ǉ�
	vec4 pos = vec4(inPosition, 1.0);
	// �N���b�v��ԍ��W�ɕϊ����Đݒ�
	gl_Position = uViewProjection * uWorldTransform * pos;

	// ���[���h���W�ɕϊ�����
	fragNormal = (uWorldTransform * vec4(inNormal, 0.0)).xyz;

	fragTexCoord = inTexCoord;
}