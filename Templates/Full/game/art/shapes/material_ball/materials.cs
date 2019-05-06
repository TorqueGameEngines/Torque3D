
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
   diffuseMap[0] = "art/pbr/gold/albedo.png";
   normalMap[0] = "art/pbr/gold/normal.png";
   roughMap[0] = "art/pbr/gold/roughness.png";
   metalMap[0] = "art/pbr/gold/metallic.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};

singleton Material(Mat_plastic_material_ball)
{
   mapTo = "plastic_material_ball";
   diffuseMap[0] = "art/pbr/plastic/plastic_A.dds";
   normalMap[0] = "art/pbr/plastic/plastic_N.dds";
   roughMap[0] = "art/pbr/plastic/roughness.png";
   aoMap[0] = "art/pbr/plastic/ao.png";
   metalMap[0] = "art/pbr/plastic/metallic.png";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   invertSmoothness[0] = "1";
   materialTag0 = "pbr";
};

singleton Material(Mat_iron_material_ball)
{
   mapTo = "iron_material_ball";
   diffuseMap[0] = "art/pbr/rusted_iron/albedo.png";
   normalMap[0] = "art/pbr/rusted_iron/normal.png";
   roughMap[0] = "art/pbr/rusted_iron/roughness.png";
   aoMap[0] = "art/pbr/rusted_iron/ao.png";
   metalMap[0] = "art/pbr/rusted_iron/metallic.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};

singleton Material(Mat_greasy_material_ball)
{
   mapTo = "greasy_material_ball";
   diffuseMap[0] = "art/pbr/greasy/greasy-pan-2-albedo.png";
   normalMap[0] = "art/pbr/greasy/greasy-pan-2-normal.png";
   roughMap[0] = "art/pbr/greasy/greasy-pan-2-roughness.png";
   metalMap[0] = "art/pbr/greasy/greasy-pan-2-metal.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};

singleton Material(Mat_copper_material_ball)
{
   mapTo = "copper_material_ball";
   diffuseMap[0] = "art/pbr/copper/oxidized-copper-albedo.png";
   normalMap[0] = "art/pbr/copper/oxidized-copper-normal-ue.png";
   roughMap[0] = "art/pbr/copper/oxidized-coppper-roughness.png";
   metalMap[0] = "art/pbr/copper/oxidized-copper-metal.png";
   invertSmoothness[0] = "1";
   useAnisotropic[0] = "1";
   translucentBlendOp = "None";
   materialTag0 = "pbr";
};
