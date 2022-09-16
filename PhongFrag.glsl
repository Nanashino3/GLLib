#version 460 core

uniform vec3 uCameraPos;	// カメラ座標
uniform float uSpecPower;	// 鏡面反射指数(a)
uniform vec3 uAmbientColor;	// 環境光(Ka)

// 平行光源
struct DirectionalLight
{
	vec3 mDirection;	// 光源の向き
	vec3 mDiffuseColor;	// 拡散反射色(Kd)
	vec3 mSpecColor;	// 鏡面反射色(Ks)
};
uniform DirectionalLight uDirLight;

in vec3 fragNormal;		// 法線座標
in vec3 fragWorldPos;	// ワールド座標

out vec4 outColor;

void main()
{
	// 計算に必要な向きを正規化しておく
	vec3 N = normalize(fragNormal);					// 法線
	vec3 L = normalize(-uDirLight.mDirection);		// 表面→光源
	vec3 V = normalize(uCameraPos - fragWorldPos);	// 表面→視点
	vec3 R = normalize(reflect(-L, N));				// Nを軸としてLを反射させたもの

	// 環境光(Ka)を代入しておく
	vec3 Phong = uAmbientColor;

	// NとLの内積を求める
	float NdotL = dot(N, L);
	if(NdotL > 0)
	{
		// 拡散反射光
		// Kd * N・L
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;

		// 鏡面反射光
		// Ks * (R・V)^a
		vec3 Specular = uDirLight.mSpecColor * pow(max(dot(R, V),0.0), uSpecPower);

		Phong += Diffuse + Specular;
	}

	outColor = vec4(Phong, 1.0);
}