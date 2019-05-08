
singleton Material(Mat_base_material_ball)
{
   mapTo = "base_material_ball";
   diffuseColor[0] = "1 1 1 1";
   smoothness[0] = "1";
   metalness[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};

singleton Material(Mat_gold_material_ball)
{
   mapTo = "gold_material_ball";
   diffuseMap[0] = "data/pbr/images/gold_albedo.png";
   normalMap[0] = "data/pbr/images/gold_normal.png";
   roughMap[0] = "data/pbr/images/gold_roughness.png";
   metalMap[0] = "data/pbr/images/gold_metallic.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};

singleton Material(Mat_plastic_material_ball)
{
   mapTo = "plastic_material_ball";
   diffuseMap[0] = "data/pbr/images/plastic_A.dds";
   normalMap[0] = "data/pbr/images/plastic_N.dds";
   roughMap[0] = "data/pbr/images/plastic_roughness.png";
   aoMap[0] = "data/pbr/images/ao.png";
   metalMap[0] = "data/pbr/images/plastic_metallic.png";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   invertSmoothness[0] = "1";
   materialTag0 = "pbr";
};

singleton Material(Mat_iron_material_ball)
{
   mapTo = "iron_material_ball";
   diffuseMap[0] = "data/pbr/images/rustediron_albedo.png";
   normalMap[0] = "data/pbr/images/rustediron_normal.png";
   roughMap[0] = "data/pbr/images/rustediron_roughness.png";
   aoMap[0] = "data/pbr/images/rustediron_ao.png";
   metalMap[0] = "data/pbr/images/rustediron_metallic.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};

singleton Material(Mat_greasy_material_ball)
{
   mapTo = "greasy_material_ball";
   diffuseMap[0] = "data/pbr/images/greasy-pan-2-albedo.png";
   normalMap[0] = "data/pbr/images/greasy-pan-2-normal.png";
   roughMap[0] = "data/pbr/images/greasy-pan-2-roughness.png";
   metalMap[0] = "data/pbr/images/greasy-pan-2-metal.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};

singleton Material(Mat_copper_material_ball)
{
   mapTo = "copper_material_ball";
   diffuseMap[0] = "data/pbr/images/oxidized-copper-albedo.png";
   normalMap[0] = "data/pbr/images/oxidized-copper-normal-ue.png";
   roughMap[0] = "data/pbr/images/oxidized-coppper-roughness.png";
   metalMap[0] = "data/pbr/images/oxidized-copper-metal.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};

singleton Material(Floor_Material)
{
   mapTo = "floor_mat";
   diffuseMap[0] = "data/pbr/images/FloorEbony_basecolor.png";
   normalMap[0] = "data/pbr/images/FloorEbony_normal.png";
   roughMap[0] = "data/pbr/images/FloorEbony_rough.png";
   aoMap[0] = "data/pbr/images/FloorEbony_ao.png";
   metalMap[0] = "data/pbr/images/FloorEbony_metal.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};
