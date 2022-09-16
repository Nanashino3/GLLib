#version 460 core

uniform vec3 uAmbientColor;	// 環境光(Ka)

// 平行光源
struct DirectionalLight
{
	vec3 mDirection;	// 光源の向き
	vec3 mDiffuseColor;	// 拡散反射色(Kd)
};
uniform DirectionalLight uDirLight;

in vec3 fragNormal;		// 法線座標
out vec4 outColor;

void main()
{
	// 計算に必要な向きを正規化しておく
	vec3 N = normalize(fragNormal);				// 法線
	vec3 L = normalize(-uDirLight.mDirection);	// 表面→光源

	// 環境光を代入しておく
	vec3 Lambert = uAmbientColor;

	// NとLの内積を求める
	float NdotL = dot(N, L);
	if(NdotL > 0)
	{
		// 拡散反射光 * (正規化したNベクトル ・ 正規化したLベクトル)
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
		Lambert += Diffuse;
	}

	outColor = vec4(Lambert, 1.0);
}