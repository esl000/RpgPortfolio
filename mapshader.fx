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

float4x4 g_matWorld : World;
float4x4 g_matView : View;
float4x4 g_matProjection : Projection;
float4   g_vWorldLightDirection
<
   string UIName = "g_vWorldLightDirection";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  true;
> = float4( 0.00, -1.00, 0.00, 0.00 );
float4   g_vWorldCameraPos : ViewPosition;
float    g_fFogStart
<
   string UIName = "g_fFogStart";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 150.00 );
float    g_fFogEnd
<
   string UIName = "g_fFogEnd";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 400.00 );
float    g_fLevelDistanse
<
   string UIName = "g_fLevelDistanse";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 80.00 );


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
   float3  m_vFog : TEXCOORD4;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.m_vPosition = mul( Input.m_vPosition, g_matWorld );
   
   float3 vWorldViewDir = Output.m_vPosition.xyz - g_vWorldCameraPos.xyz;
   Output.m_vViewDir = normalize(vWorldViewDir);
   
   Output.m_vPosition = mul( Output.m_vPosition, g_matView );
   Output.m_vPosition = mul( Output.m_vPosition, g_matProjection );
   
   float3 vWorldNormal = mul(Input.m_vNormal, g_matWorld);
   vWorldNormal = normalize(vWorldNormal);
   
   Output.m_vDiffuse = dot(-g_vWorldLightDirection, vWorldNormal);
   Output.m_vReflect = reflect(g_vWorldLightDirection, vWorldNormal);
   
   Output.m_vTexCoord = Input.m_vTexCoord;
   
   float1 fDistanse = length(g_vWorldCameraPos - Input.m_vPosition);
   Output.m_vFog = float3(0.f, 0.f, 0.f);
   
   if(fDistanse < g_fFogStart)
   {
      Output.m_vFog.x = 0.f;
   }
   else
   {
      Output.m_vFog.x = (fDistanse - g_fFogStart) / g_fFogEnd;
      if(Output.m_vFog.x > 1.f)
      {
         Output.m_vFog.x = 1.f;
      }
   }
   
   Output.m_vFog.y = (int)(fDistanse / g_fLevelDistanse);
  
   
   return( Output );
   
}




texture DurotarDirt_Tex
<
   string ResourceName = ".\\DurotarDirt.png";
>;
sampler2D DiffuseSampler1 = sampler_state
{
   Texture = (DurotarDirt_Tex);
};
texture DurotarDirtSmooth_Tex
<
   string ResourceName = ".\\DurotarDirtSmooth.png";
>;
sampler2D DiffuseSampler2 = sampler_state
{
   Texture = (DurotarDirtSmooth_Tex);
};
texture DurotarGrass_Tex
<
   string ResourceName = ".\\DurotarGrass.png";
>;
sampler2D DiffuseSampler3 = sampler_state
{
   Texture = (DurotarGrass_Tex);
};

texture kalimdor_37_32adt_Heightmap_LOD_Tex
<
   string ResourceName = ".\\kalimdor_37_32adt_Heightmap_LOD.png";
>;
sampler2D BlendingSampler = sampler_state
{
   Texture = (kalimdor_37_32adt_Heightmap_LOD_Tex);
};

sampler2D SpecularSampler1;
sampler2D SpecularSampler2;
sampler2D SpecularSampler3;

struct PS_INPUT 
{
   float3 m_vDiffuse : TEXCOORD1;
   float3 m_vViewDir : TEXCOORD2;
   float3 m_vReflect : TEXCOORD3;
   float2 m_vTexCoord : TEXCOORD0;
   float3  m_vFog : TEXCOORD4;
};

float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{   
   float4 vFogColor = float4(0.7f, 0.7f, 0.7f, 1.f);

   float4 vBlending = tex2D(BlendingSampler, Input.m_vTexCoord / 3.f);
   
   //float4 vTexCoord = float4(Input.m_vTexCoord.x, Input.m_vTexCoord.y , 0, Input.m_vFog.y);
   
   float4 vSampler1 = tex2D(DiffuseSampler1, Input.m_vTexCoord);
   float4 vSampler2 = tex2D(DiffuseSampler2, Input.m_vTexCoord);
   float4 vSampler3 = tex2D(DiffuseSampler3, Input.m_vTexCoord);
   
   float3 vMul = (vSampler1.rgb * vBlending.r) +
                      (vSampler2.rgb * vBlending.g) +
                      (vSampler3.rgb * vBlending.b);
                      
                      //(vSampler1.rgb * vBlending.r) *
                      //(vSampler2.rgb * vBlending.g) *
                      //(vSampler3.rgb * vBlending.b)
   
   float3 vDiffuse = ((1 - Input.m_vFog.x) * vMul + Input.m_vFog.x * vFogColor.xyz) * saturate(Input.m_vDiffuse);
                        
   float3 vReflect = normalize(Input.m_vReflect);
   float3 vViewDir = normalize(Input.m_vViewDir);
   //float3 vSpecular = 0.0f;
   
   //if(vDiffuse.r > 0.0f)
   //{
   //   vSampler1 = tex2Dlod(SpecularSampler1, vTexCoord);
   //   vSampler2 = tex2Dlod(SpecularSampler2, vTexCoord);
   //   vSampler3 = tex2Dlod(SpecularSampler3, vTexCoord);
      
   //   vMul = (vSampler1.rgb * vBlending.r) +
   //                   (vSampler2.rgb * vBlending.g) +
   //                   (vSampler3.rgb * vBlending.b);
                      
      //float4 vIntencity = tex2D(SpecularSampler, Input.m_vTexCoord);
   //   vSpecular = (1 - Input.m_vFog.x) * saturate(dot(vReflect, -vViewDir));
   //   vSpecular = 0.2f * ((1 - Input.m_vFog.x) * vMul + Input.m_vFog.x * vFogColor.xyz) * pow(vSpecular, 20.f);
   //}
   
   return float4(vDiffuse, Input.m_vFog.x) ;
   
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_3_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

