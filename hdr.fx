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

float4x4 g_matViewProjection;
float4   g_vWorldCameraPos;

struct VS_INPUT 
{
   float4 m_vPosition : POSITION0;
};

struct VS_OUTPUT 
{
   float4 m_vPosition : POSITION0;
   float2 m_vTexCoord : TEXCOORD0;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   // get into range [0,1]
   Output.m_vPosition = float4( Input.m_vPosition.xy, 0.0f, 1.0f);

   // get into range [0,1]
   Output.m_vTexCoord = (float2(Output.m_vPosition.x, -Output.m_vPosition.y) + 1.0f)/2.0f;
   
   //Output.m_vPosition = mul(Input.m_vPosition, g_matViewProjection);
   //Output.m_vTexCoord = float2(Output.m_vPosition.x + 256.f, -Output.m_vPosition.y - 256.f) / 256.0f;
   //Output.m_vTexCoord = Input.m_vTexCoord;
   return( Output );
   
}




texture Coin_Tex
<
   string ResourceName = "C:\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Coin.dds";
>;
sampler2D RenderSampler = sampler_state
{
   Texture = (Coin_Tex);
};
float    g_fHdrDistanse;

float4 gaussFilter[7] = 
{ 
   -3.0, -3.0, 0.0,  1.0/64.0,
   -2.0, -2.0, 0.0,  6.0/64.0,
   -1.0, -1.0, 0.0, 15.0/64.0,
   0.0, 0.0, 0.0, 20.0/64.0,
   1.0, 1.0, 0.0, 15.0/64.0,
   2.0, 2.0, 0.0,  6.0/64.0,
   3.0, 3.0, 0.0,  1.0/64.0 
};

float texScaler = 1 / 128.0;
float texOffset = 0.0;

struct PS_INPUT 
{
   float2 m_vTexCoord : TEXCOORD0;
   float m_fDistanse : TEXCOORD1;
};


float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{   
   float4 vColor = tex2D(RenderSampler, Input.m_vTexCoord);
   float4 m_vColor = 0.0;
   
   for(int i = 0; i < 7; ++i)
   {
      for(int j = 0; j < 7; ++j)
      {
         m_vColor +=tex2D(RenderSampler, float2(Input.m_vTexCoord.x + gaussFilter[i].x * texScaler + texOffset,
                                                Input.m_vTexCoord.y + gaussFilter[j].y * texScaler + texOffset)) * (gaussFilter[i].w * gaussFilter[j].w);
      }
   }
   
   float m_fHdrPer = Input.m_fDistanse / g_fHdrDistanse;
   
   if(m_fHdrPer >= 1.f)
   {
      m_fHdrPer = 1.f;
   }
   m_vColor = (1 - vColor.a) * tex2D(RenderSampler, Input.m_vTexCoord) + vColor.a * m_vColor;
   //m_vColor = tex2D(RenderSampler, Input.m_vTexCoord);
   return(m_vColor);
  //return (1.f, 0.f, 0.f, 0.f)
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

