Texture2D txDiffuse : register(t0);

SamplerState samLinear : register(s0);

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

struct VS_OUTPUT
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;
	float3 NormW : NORMAL;
	float2 Tex : TEXCOORD0;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
};

float4 main(VS_OUTPUT input) : SV_Target
{
	float4 color = (0.0f, 0.0f, 0.0f, 0.0f);

	float3 diffuse = { 0.0f, 0.0f, 0.0f };
	float3 ambient = { 0.0f, 0.0f, 0.0f };
	float3 specular = { 0.0f, 0.0f, 0.0f };

	input.NormW = normalize(input.NormW);

	float3 toEye = EyePosW - input.PosW.xyz;
	float distToEye = length(toEye);
	toEye = normalize(toEye);

	float4 texColor = (1.0f, 1.0f, 1.0f, 1.0f);
	texColor = txDiffuse.Sample(samLinear, input.Tex);

	float3 reflection = reflect(-light.LightVecW, input.NormW);
	float diffuseAmount = max(dot(light.LightVecW, input.NormW), 0.0f);
	float specularAmount = pow(max(dot(reflection, toEye), 0.0f), light.SpecularPower);

	diffuse = diffuseAmount * (surface.DiffuseMtrl * light.DiffuseLight).rgb;
	ambient = (surface.AmbientMtrl * light.AmbientLight).rgb;

	if (all(diffuse) <= 0.0f)
	{
		specular = (0.0f, 0.0f, 0.0f);
	}
	else
	{
		specular = specularAmount * (surface.SpecularMtrl * light.SpecularLight).rgb;
	}

	color.rgb = clamp(texColor*(diffuse + ambient) + specular, 0, 1);

	return color;
}