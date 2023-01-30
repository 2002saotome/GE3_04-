#include "Basic.hlsli"

Texture2D<float4> tex : register(t0);  	// 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      	// 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = float4(tex.Sample(smp, input.uv));

    // 右下奥　向きのライト
    float3 light = normalize(float3(1,-1,1));
    // 光源へのベクトルと法線ベクトルの内積
    float diffuse = saturate(dot(-light, input.normal));
    // アンビエント光を0.3として計算
    float ambient = 0.3f;
    // 明るさを計算
    float brightness = diffuse + ambient;
    // テクスチャとシェーディングによる色を合成
    return float4(texcolor.rgb * brightness, texcolor.a) * color;
}