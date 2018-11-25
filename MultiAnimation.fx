//--------------------------------------------------------------------------------------
// File: ShadowVolume.fx
//
// The effect file for the MultiAnimation sample.  
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


#include "MultiAnimation.vsh"


float4 lhtDir;					// = { 1.0f, -1.0f, 0.0f, 1.0f };  // Light Direction
float4 lightDiffuse;			// = { 1.0f, 1.0f, 1.0f, 1.0f };   // Light Diffuse
float4 MaterialAmbient;		// : MATERIALAMBIENT = { 1.0f, 0.1f, 0.1f, 1.0f };
float4 MaterialDiffuse;		// : MATERIALDIFFUSE = { 0.8f, 0.8f, 0.8f, 1.0f };

float4x4 g_mWorld : WORLD;
float4x4 g_mViewProj : VIEWPROJECTION;
float4   vWorldLightPos
<
   string UIName = "vWorldLightPos";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 0.00, 500.00, -500.00, 1.00 );
float4   vWorldCameraPos
<
   string UIName = "vWorldCameraPos";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( -50.00, 50.00, -50.00, 1.00 );

texture g_txScene;


//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler g_samScene =
sampler_state
{
    Texture = <g_txScene>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Point;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float3  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3  Tex0            : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 Pos     : POSITION;
    float4 Diffuse : COLOR0;
    float2 Tex0    : TEXCOORD0;
	float3 fDiffuse    : TEXCOORD1;
    float3 fViewDir    : TEXCOORD2;
    float3 fReflection : TEXCOORD3;
};


VS_OUTPUT VertScene( VS_INPUT Input )
{
    VS_OUTPUT Output;
    
    Output.Pos = mul( Input.Pos, g_mWorld );
	
	float3 lightDir = Output.Pos.xyz - vWorldLightPos.xyz;
	lightDir = normalize(lightDir);
    
	float3 ViewDir = Output.Pos.xyz - vWorldCameraPos.xyz;
	Output.fViewDir = normalize(ViewDir);
	
	///World End
    Output.Pos = mul( Output.Pos, g_mViewProj );
	
	float3 worldNormal = mul(Input.Normal, (float3x3)g_mWorld);
	worldNormal = normalize(worldNormal);
    
	Output.fDiffuse = dot(-lightDir, worldNormal);
	Output.fReflection = reflect(lightDir, worldNormal);
   
    // Always fully lit the floor
    Output.Diffuse = 1.0f;
    Output.Tex0 = Input.Tex0;

    return Output;
}


float4 PixScene( float4 Diffuse : COLOR0,
                 float2 Tex0 : TEXCOORD0,
				 float3 fDiffuse    : TEXCOORD1,
				 float3 fViewDir    : TEXCOORD2,
				 float3 fReflection : TEXCOORD3) : COLOR0
{
////////////////////////////
	float3 color = saturate(Diffuse);
   
	float3 reflaction = normalize(fReflection);
	float3 viewDir = normalize(fViewDir);
   
	float3 specular = 0;
    if(color.x > 0)
	{
		specular = saturate(dot(reflaction, -viewDir));
		specular = pow(specular, 20.0f);	
	}
   
////////////////////////////
	float4 Color = tex2D( g_samScene, Tex0 ) * float4(color + specular, 1.0f);
	return Color;
}


VS_OUTPUT VertSkinning( VS_INPUT i, uniform int iNumBones )
{
    VS_OUTPUT   Output;
	Output.fDiffuse    = float3(0,0,0);
	Output.fViewDir    = float3(0,0,0);
	Output.fReflection = float3(0,0,0);
    float3      Pos = 0.0f;
    float3      Normal = 0.0f;
    float       LastWeight = 0.0f;
    
    // skin VB inputs
    VS_SKIN_INPUT vsi = { i.Pos, i.BlendWeights, i.BlendIndices, i.Normal };
    VS_SKIN_OUTPUT vso = VS_Skin( vsi, iNumBones );

    // transform position from world space into view and then projection space
    Output.Pos = mul( float4( vso.vPos.xyz, 1.0f ), g_mViewProj );

    // normalize normals
    Normal = normalize( vso.vNor );

    // Shade (Ambient + etc.)
    Output.Diffuse = float4( MaterialAmbient.xyz + saturate( dot( Normal, lhtDir.xyz ) ) * MaterialDiffuse.xyz, 1.0 );

    // copy the input texture coordinate through
    Output.Tex0  = i.Tex0.xy;
	







	

	float3 lightDir = vso.vPos.xyz - vWorldLightPos.xyz;
	lightDir = normalize(lightDir);
    
	float3 ViewDir = vso.vPos.xyz - vWorldCameraPos.xyz;
	Output.fViewDir = normalize(ViewDir);
	
	float3 worldNormal = normalize(Normal);
    
	Output.fReflection = reflect(lightDir, worldNormal);
   
    
    






    return Output;
}


int CurNumBones = 10;

VertexShader vsArray20[ 4 ] = { compile vs_2_0 VertSkinning( 1 ),
                                compile vs_2_0 VertSkinning( 2 ),
                                compile vs_2_0 VertSkinning( 3 ),
                                compile vs_2_0 VertSkinning( 4 ) };


//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------


technique RenderScene
{
    pass p0
    {
        VertexShader = compile vs_2_0 VertScene();
        PixelShader = compile ps_2_0 PixScene();
    }
}


technique Skinning20
{
    pass p0
    {
        VertexShader = ( vsArray20[ CurNumBones ] );
        PixelShader = compile ps_2_0 PixScene();
    }
}
