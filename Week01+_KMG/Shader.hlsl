// Shader.hlsl

cbuffer cbGameObjectInfo : register(b0)
{
    row_major float4x4 mvp;
}

struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;

    output.position = float4(input.position, 1);
    output.color = input.color;

    return output;
}

float4 PS(PS_INPUT input) : SV_TARGET
{
    return (float4(1,0,0,1));
    
}
