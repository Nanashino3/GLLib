#version 460 core
uniform mat4 uWorldTransform;	// ���[���h�ϊ����W
uniform mat4 uViewProjection;	// �r���[�ˉe�s��

in vec3 inPosition;				// �ʒu���W
in vec3 inNormal;				// �@�����W

out vec3 fragNormal;
out vec3 fragWorldPos;

void main()
{
	// w������ǉ�
	vec4 pos = vec4(inPosition, 1.0);
	// �N���b�v��ԍ��W�ɕϊ����Đݒ�
	gl_Position = uViewProjection * uWorldTransform * pos;

	// ���[���h���W�ɕϊ�����
	fragNormal = (uWorldTransform * vec4(inNormal, 0.0)).xyz;
	fragWorldPos = (uWorldTransform * pos).xyz;
}