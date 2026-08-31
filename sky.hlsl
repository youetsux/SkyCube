// 頂点バッファを使わず、SV_VertexID だけで画面全体を覆う三角形を作る。

struct VS_OUT
{
    float4 pos : SV_POSITION;
};

VS_OUT VS(uint id : SV_VertexID)
{
    VS_OUT output;

    float2 uv = float2(0.0, 0.0);
    if (id == 0)
        uv = float2(0.0, 0.0);
    else if (id == 1)
        uv = float2(2.0, 0.0);
    else if (id == 2)
        uv = float2(0.0, 2.0);

    // この段階では通常の LESS 深度判定でも通るように z を少しだけ手前へ置く。
    output.pos = float4(uv * float2(2, -2) + float2(-1, 1), 0.999f, 1.0f);
    return output;
}

float4 PS(VS_OUT input) : SV_Target
{
    // まずはキューブマップを使わず、空の描画経路だけを確認する。
    return float4(0.18f, 0.35f, 0.65f, 1.0f);
}
