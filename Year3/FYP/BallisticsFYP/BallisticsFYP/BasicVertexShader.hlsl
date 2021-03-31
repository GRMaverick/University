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
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
};

struct VS_OUTPUT
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;
	float3 NormW : NORMAL;
	float2 Tex : TEXCOORD0;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
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

	//
	//		Interpolated for NormalMap Calculation
	//
	output.Tangent = mul(input.Tangent, (float3x3)World);
	output.Tangent = normalize(output.Tangent);
	output.Binormal = mul(input.Binormal, (float3x3)World);
	output.Binormal = normalize(output.Binormal);
	//

	return output;
}