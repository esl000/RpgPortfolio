//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Default_DirectX_Effect_Pass_0_Model : ModelData = "C:\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 g_matView : View;
float4x4 g_matWorld : World;
float4x4 g_matProjection : Projection;
float4   g_vWorldLightDirection
<
   string UIName = "g_vWorldLightDirection";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  true;
> = float4( 0.00, -0.71, -0.71, 0.00 );
float4   g_vWorldCameraPos : ViewPosition;

struct VS_INPUT 
{
   float4 m_vPosition : POSITION0;
   float3 m_vNormal : NORMAL;
   float2 m_vTexCoord : TEXCOORD0;
   
};

struct VS_OUTPUT 
{
   float4 m_vPosition : POSITION0;
   float2 m_vTexCoord : TEXCOORD0;
   float3 m_vDiffuse : TEXCOORD1;
   float3 m_vViewDir : TEXCOORD2;
   float3 m_vReflect : TEXCOORD3;
   float  m_fFog : TEXCOORD4;  
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.m_vPosition = mul( Input.m_vPosition, g_matWorld );
   
   float4 vPosition = Output.m_vPosition;
   
   float3 vWorldViewDir = Output.m_vPosition.xyz - g_vWorldCameraPos.xyz;
   Output.m_vViewDir = normalize(vWorldViewDir);
   
   Output.m_vPosition = mul( Output.m_vPosition, g_matView );
   Output.m_vPosition = mul( Output.m_vPosition, g_matProjection );
   
   float3 vWorldNormal = mul(Input.m_vNormal, g_matWorld);
   vWorldNormal = normalize(vWorldNormal);
   
   Output.m_vDiffuse = dot(-g_vWorldLightDirection, vWorldNormal);
   Output.m_vReflect = reflect(g_vWorldLightDirection, vWorldNormal);
   
   Output.m_vTexCoord = Input.m_vTexCoord;
   
   float1 fDistanse = length(g_vWorldCameraPos - vPosition);
   
   if(fDistanse < 150.f)
   {
      Output.m_fFog = 0.f;
   }
   else
   {
      Output.m_fFog = (fDistanse - 150.f) / 400.f;
      if(Output.m_fFog > 1.f)
      {
         Output.m_fFog = 1.f;
      }
   }
   
   
   return( Output );
   
}




texture Coin_Tex
<
   string ResourceName = "C:\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Coin.dds";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (Coin_Tex);
};

struct PS_INPUT 
{
   float2 m_vTexCoord : TEXCOORD0;
   float3 m_vDiffuse : TEXCOORD1;
   float3 m_vViewDir : TEXCOORD2;
   float3 m_vReflect : TEXCOORD3;  
   float m_fFog : TEXCOORD4; 
};

float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{      

   float4 vFogColor = float4(0.7f, 0.7f, 0.7f, 1.f);
   
   float4 vTexColor = tex2D(DiffuseSampler, Input.m_vTexCoord);
   float3 vDiffuse = saturate(Input.m_vDiffuse) + 0.15f;
   if(vDiffuse.x > 1.f)
   {
      vDiffuse = float3(1.f, 1.f, 1.f);
   }
   
   vDiffuse = ((1 - Input.m_fFog) * vTexColor.rgb + Input.m_fFog * vFogColor.rgb) * vDiffuse;
   
	  float4 vColor;

   if(vTexColor.a <0.5f)
  	vColor = float4(vDiffuse, 0.0f);
   else
	vColor = float4(vDiffuse, 1.0f);	

   return( vColor );
   
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

