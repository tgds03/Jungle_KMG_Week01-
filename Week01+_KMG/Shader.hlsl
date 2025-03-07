// ShaderW0.hlsl
struct VS_INPUT
{
    float4 position : POSITION; // Input position from vertex buffer
    float4 color : COLOR; // Input color from vertex buffer
};
struct PS_INPUT
{
    float4 position : SV_POSITION; // Transformed position to pass to the pixel shader
    float4 color : COLOR; // Color to pass to the pixel shader
};
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;
    output.position = input.position;
    output.color = input.color;
    return output;
}
float4 PS(PS_INPUT input) : SV_TARGET
{
    // Output the color directly
    return input.color;
}