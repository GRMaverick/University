//// A constant buffer that stores the three basic column-major matrices for composing geometry.
//cbuffer ModelViewProjectionConstantBuffer : register(b0)
//{
//	matrix model;
//	matrix view;
//	matrix projection;
//};
//
//// Per-vertex data used as input to the vertex shader.
//struct VertexShaderInput
//{
//	float3 pos : POSITION;
//	float3 color : COLOR0;
//};
//
//// Per-pixel color data passed through the pixel shader.
//struct PixelShaderInput
//{
//	float4 pos : SV_POSITION;
//	float3 color : COLOR0;
//};
//
//// Simple shader to do vertex processing on the GPU.
//PixelShaderInput main(VertexShaderInput input)
//{
//	PixelShaderInput output;
//	float4 pos = float4(input.pos, 1.0f);
//
//	// Transform the vertex position into projected space.
//	pos = mul(pos, model);
//	pos = mul(pos, view);
//	pos = mul(pos, projection);
//	output.pos = pos;
//
//	// Pass the color through without modification.
//	output.color = input.color;
//
//	return output;
//}

struct SurfaceInfo
{
	float4 AmbientMtrl;
	float4 DiffuseMtrl;
	float4 SpecularMtrl;
};

struct Light
{
	float4 AmbientLight;
	float4 DiffuseLight;
	float4 SpecularLight;

	float SpecularPower;
	float3 LightVecW;
};

cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;

	SurfaceInfo surface;
	Light light;

	float3 EyePosW;
	float HasTexture;
	float HasNormalTexture;
}

struct VS_INPUT
{
	float4 PosL : POSITION;
	float3 NormL : NORMAL;
	float2 Tex : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;
	float3 NormW : NORMAL;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float4 posW = mul(input.PosL, World);
	output.PosW = posW.xyz;
	output.PosH = mul(posW, View);
	output.PosH = mul(output.PosH, Projection);

	output.Tex = input.Tex;

	float3 normalW = mul(float4(input.NormL, 0.0f), World).xyz;
	output.NormW = normalize(normalW);

	return output;
}