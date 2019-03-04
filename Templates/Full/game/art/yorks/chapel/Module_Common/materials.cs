//yorks chapel

singleton Material(LMA_chapel_int_chapel_Module_Common_LMA_chapel_int_Material0)
{
	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = "0";
	emissive[0] = "0";
	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	mapTo = "chapel_Module_Common_LMA_chapel_int-Material0";
	diffuseMap[0] = "art/shapes/yorks/chapel/brick_block_dds.dds";
   diffuseColor[1] = "1 1 1 1";
   materialTag0 = "urban";
   pixelSpecular[1] = "0";
   useAnisotropic[1] = "0";
   emissive[1] = "1";
   lightMap[1] = "art/shapes/yorks/chapel/Module_Common/LMA_chapel_int.dds";
   diffuseMap[1] = "art/shapes/yorks/chapel/brick_block_alpha.dds";
   cubemap = "DesertSkyCubemap";
   toneMap[0] = "art/shapes/yorks/chapel/Module_Common/LMA_chapel_int.dds";
   specularMap[0] = "art/shapes/yorks/chapel/brick_block_dds.dds";
};

singleton Material(LMA_chapel_int_chapel_Module_Common_LMA_chapel_int_Material1)
{
	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = "0";
	emissive[0] = "0";
	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	mapTo = "chapel_Module_Common_LMA_chapel_int-Material1";
	diffuseMap[0] = "art/shapes/yorks/chapel/brick_small_blue_dds.dds";
   diffuseColor[1] = "1 1 1 1";
   materialTag0 = "urban";
   pixelSpecular[1] = "0";
   useAnisotropic[1] = "0";
   emissive[1] = "1";
   lightMap[1] = "art/shapes/yorks/chapel/Module_Common/LMA_chapel_int.dds";
   diffuseMap[1] = "art/shapes/yorks/chapel/brick_small_blue_alpha.dds";
   cubemap = "DesertSkyCubemap";
   toneMap[0] = "art/shapes/yorks/chapel/Module_Common/LMA_chapel_int.dds";
   specularMap[0] = "art/shapes/yorks/chapel/brick_small_blue_dds.dds";
};

singleton Material(LMX_chapel_props_chapel_Module_Common_LMX_chapel_props_Material0)
{
   mapTo = "chapel_Module_Common_LMX_chapel_props-Material0";
   diffuseColor[1] = "1 1 1 0.8";
   diffuseMap[0] = "art/shapes/yorks/chapel/marble1_red.png";
   diffuseMap[1] = "art/shapes/yorks/chapel/marble1_red.png";
   toneMap[0] = "art/shapes/yorks/chapel/Module_Common/LMX_chapel_props.dds";
   emissive[1] = "1";
   translucentBlendOp = "None";
   emissive[0] = "0";
   materialTag0 = "Miscellaneous";
   alphaRef = "0";
   lightMap[1] = "art/shapes/yorks/chapel/Module_Common/LMX_chapel_props.dds";
   castShadows = "0";
   cubemap = "DesertSkyCubemap";
   showFootprints = "0";
};

singleton Material(LMX_chapel_props_chapel_Module_Common_LMX_chapel_props_Material1)
{
	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = "0";
	emissive[0] = false;
	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	mapTo = "chapel_Module_Common_LMX_chapel_props-Material1";
	toneMap[0] = "art/shapes/yorks/chapel/Module_Common/LMX_chapel_props.dds";
	diffuseMap[0] = "art/shapes/yorks/chapel/marble1_green.png";
   diffuseColor[1] = "1 1 1 0.7";
   diffuseMap[1] = "art/shapes/yorks/chapel/marble1_green.png";
   lightMap[1] = "art/shapes/yorks/chapel/Module_Common/LMX_chapel_props.dds";
   emissive[1] = "1";
   materialTag0 = "Miscellaneous";
   cubemap = "DesertSkyCubemap";
};

singleton Material(LMX_chapel_props_chapel_Module_Common_LMX_chapel_props_Material2)
{
	diffuseColor[0] = "1 1 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = true;
	emissive[0] = false;
	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	mapTo = "chapel_Module_Common_LMX_chapel_props-Material2";
	toneMap[0] = "art/shapes/yorks/chapel/Module_Common/LMX_chapel_props.dds";
	diffuseMap[0] = "art/shapes/yorks/chapel/int_props_map.png";
   diffuseColor[1] = "1 1 1 0.7";
   diffuseMap[1] = "art/shapes/yorks/chapel/int_props_map.png";
   lightMap[1] = "art/shapes/yorks/chapel/Module_Common/LMX_chapel_props.dds";
   emissive[1] = "1";
   cubemap = "DesertSkyCubemap";
};

singleton Material(SB_chapel_glass_chapel_Module_Common_SB_chapel_glass_Material0)
{
	diffuseColor[0] = "0.6 0.5 0.4 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = "0";
	emissive[0] = "1";
	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	mapTo = "chapel_Module_Common_SB_chapel_glass-Material0";
   diffuseMap[0] = "art/shapes/yorks/chapel/stainedglass1.png";
   glow[0] = "1";
   materialTag0 = "Miscellaneous";
};

singleton Material(BlankWhite)
{
   mapTo = "chapel_Module_Common_SB_chapel_ext-Material0";
   emissive[0] = "0";
   materialTag0 = "Miscellaneous";
};
