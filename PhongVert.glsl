#version 460 core
uniform mat4 uWorldTransform;	// ワールド変換座標
uniform mat4 uViewProjection;	// ビュー射影行列

in vec3 inPosition;				// 位置座標
in vec3 inNormal;				// 法線座標

out vec3 fragNormal;
out vec3 fragWorldPos;

void main()
{
	// w成分を追加
	vec4 pos = vec4(inPosition, 1.0);
	// クリップ空間座標に変換して設定
	gl_Position = uViewProjection * uWorldTransform * pos;

	// ワールド座標に変換する
	fragNormal = (uWorldTransform * vec4(inNormal, 0.0)).xyz;
	fragWorldPos = (uWorldTransform * pos).xyz;
}