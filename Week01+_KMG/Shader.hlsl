cbuffer TransformBuffer : register(b0)
{
    matrix WorldMatrix; // 4x4 ��ȯ ���
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
    
    // ���� ��ǥ�� 4D ���ͷ� ��ȯ �� ��� ��
    output.Position = mul(float4(input.Position, 1.0f), WorldMatrix);
    //output.Position = float4(input.Position, 1.0f);
    
    // ���� ������ �״�� ����
    output.Color = input.Color;
    
    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    return input.Color; // �÷� ���
}
