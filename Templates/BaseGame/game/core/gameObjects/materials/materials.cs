singleton ShaderData( BasicRibbonShader )
{
   DXVertexShaderFile   = $Core::CommonShaderPath @ "/ribbons/basicRibbonShaderV.hlsl";
   DXPixelShaderFile    = $Core::CommonShaderPath @ "/ribbons/basicRibbonShaderP.hlsl";
 
   OGLVertexShaderFile   = $Core::CommonShaderPath @ "/ribbons/gl/basicRibbonShaderV.glsl";
   OGLPixelShaderFile    = $Core::CommonShaderPath @ "/ribbons/gl/basicRibbonShaderP.glsl";
 
   samplerNames[0] = "$ribTex";
 
   pixVersion = 2.0;
};
 
singleton CustomMaterial( BasicRibbonMat )
{
   shader = BasicRibbonShader;
   version = 2.0;
   
   emissive[0] = true;
   
   doubleSided = true;
   translucent = true;
   BlendOp = AddAlpha;
   translucentBlendOp = AddAlpha;
   
   preload = true;
};

singleton ShaderData( TexturedRibbonShader )
{
   DXVertexShaderFile   = $Core::CommonShaderPath @ "/ribbons/texRibbonShaderV.hlsl";
   DXPixelShaderFile    = $Core::CommonShaderPath @ "/ribbons/texRibbonShaderP.hlsl";
   
   OGLVertexShaderFile   = $Core::CommonShaderPath @ "/ribbons/gl/texRibbonShaderV.glsl";
   OGLPixelShaderFile    = $Core::CommonShaderPath @ "/ribbons/gl/texRibbonShaderP.glsl";
   
   samplerNames[0] = "$ribTex";
   
   pixVersion = 2.0;
};
 
singleton CustomMaterial( TexturedRibbonMat )
{
   shader = TexturedRibbonShader;
   version = 2.0;
   
   emissive[0] = true;
   
   doubleSided = true;
   translucent = true;
   BlendOp = AddAlpha;
   translucentBlendOp = AddAlpha;

   sampler["ribTex"] = "core/gameObjects/images/ribTex.png";
   
   preload = true;
};

singleton Material(DefaultDecalRoadMaterial)
{
   diffuseMap[0] = "core/gameObjects/images/defaultRoadTextureTop.png";
   mapTo = "unmapped_mat";
   materialTag0 = "RoadAndPath";
};

singleton Material(DefaultRoadMaterialTop)
{
   mapTo = "unmapped_mat";
   diffuseMap[0] = "core/gameObjects/images/defaultRoadTextureTop.png";
   materialTag0 = "RoadAndPath";
};

singleton Material(DefaultRoadMaterialOther)
{
   mapTo = "unmapped_mat";
   diffuseMap[0] = "core/gameObjects/images/defaultRoadTextureOther.png";
   materialTag0 = "RoadAndPath";
};