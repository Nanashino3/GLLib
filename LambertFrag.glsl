#version 460 core

uniform vec3 uAmbientColor;	// ����(Ka)

// ���s����
struct DirectionalLight
{
	vec3 mDirection;	// �����̌���
	vec3 mDiffuseColor;	// �g�U���ːF(Kd)
};
uniform DirectionalLight uDirLight;

in vec3 fragNormal;		// �@�����W
out vec4 outColor;

void main()
{
	// �v�Z�ɕK�v�Ȍ����𐳋K�����Ă���
	vec3 N = normalize(fragNormal);				// �@��
	vec3 L = normalize(-uDirLight.mDirection);	// �\�ʁ�����

	// �����������Ă���
	vec3 Lambert = uAmbientColor;

	// N��L�̓��ς����߂�
	float NdotL = dot(N, L);
	if(NdotL > 0)
	{
		// �g�U���ˌ� * (���K������N�x�N�g�� �E ���K������L�x�N�g��)
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
		Lambert += Diffuse;
	}

	outColor = vec4(Lambert, 1.0);
}