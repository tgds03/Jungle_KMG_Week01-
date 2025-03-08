cbuffer TransformBuffer : register(b0)
{
    row_major matrix WorldMatrix; // 4x4 변환 행렬
};

struct VS_INPUT
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    // 정점 좌표를 4D 벡터로 변환 후 행렬 곱
    output.Position = mul(float4(input.Position.xyz, 1.f), WorldMatrix);
    //output.Position = float4(input.Position, 1.0f);
    
    // 정점 색상을 그대로 전달
    output.Color = input.Color;
    
    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    return input.Color; // 컬러 출력
}
