// 頂点バッファを使わず、SV_VertexID だけで画面全体を覆う三角形を作る。

cbuffer SkyConstants : register(b0)
{
    row_major float4x4 invProj;
    row_major float4x4 invViewRot;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float3 viewDir : TEXCOORD0;
};

VS_OUT VS(uint id : SV_VertexID)
{
    VS_OUT output;

    float2 uv = float2(0.0, 0.0);
    if (id == 0)    uv = float2(0.0, 0.0);
    else if (id == 1)   uv = float2(2.0, 0.0);
    else if (id == 2)   uv = float2(0.0, 2.0);
    
    // この段階では通常の LESS 深度判定でも通るように z を少しだけ手前へ置く。
    output.pos = float4(uv * float2(2, -2) + float2(-1, 1), 0.999f, 1.0f);
    
    // 画面上の位置を、ビュー空間の位置へ戻す。
    float4 viewPos = mul(float4(output.pos.xy, 1, 1), invProj);
    viewPos.xyz /= viewPos.w;

    // ビュー空間の方向をワールド空間へ戻す。
    // w=0 なので「位置」ではなく「方向」として変換される。
    output.viewDir = mul(float4(viewPos.xyz, 0), invViewRot).xyz;
    
    return output;
}

float4 PS(VS_OUT input) : SV_Target
{
    // まずはキューブマップを使わず、空の描画経路だけを確認する。
    float3 dir = normalize(input.viewDir);
    return float4(abs(dir), 1.0f);
    //return float4(0.18f, 0.35f, 0.65f, 1.0f);
}
