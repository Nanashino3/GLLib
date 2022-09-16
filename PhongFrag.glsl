#version 460 core

uniform vec3 uCameraPos;	// �J�������W
uniform float uSpecPower;	// ���ʔ��ˎw��(a)
uniform vec3 uAmbientColor;	// ����(Ka)

// ���s����
struct DirectionalLight
{
	vec3 mDirection;	// �����̌���
	vec3 mDiffuseColor;	// �g�U���ːF(Kd)
	vec3 mSpecColor;	// ���ʔ��ːF(Ks)
};
uniform DirectionalLight uDirLight;

in vec3 fragNormal;		// �@�����W
in vec3 fragWorldPos;	// ���[���h���W

out vec4 outColor;

void main()
{
	// �v�Z�ɕK�v�Ȍ����𐳋K�����Ă���
	vec3 N = normalize(fragNormal);					// �@��
	vec3 L = normalize(-uDirLight.mDirection);		// �\�ʁ�����
	vec3 V = normalize(uCameraPos - fragWorldPos);	// �\�ʁ����_
	vec3 R = normalize(reflect(-L, N));				// N�����Ƃ���L�𔽎˂���������

	// ����(Ka)�������Ă���
	vec3 Phong = uAmbientColor;

	// N��L�̓��ς����߂�
	float NdotL = dot(N, L);
	if(NdotL > 0)
	{
		// �g�U���ˌ�
		// Kd * N�EL
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;

		// ���ʔ��ˌ�
		// Ks * (R�EV)^a
		vec3 Specular = uDirLight.mSpecColor * pow(max(dot(R, V),0.0), uSpecPower);

		Phong += Diffuse + Specular;
	}

	outColor = vec4(Phong, 1.0);
}