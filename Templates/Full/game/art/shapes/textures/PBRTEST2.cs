
singleton TSShapeConstructor(PBRTEST2Dae)
{
   baseShape = "./PBRTEST2.dae";
};

function PBRTEST2Dae::onLoad(%this)
{
   %this.addNode("Col-1", "", "0 0 0 0 0 1 0", "0");
   %this.addCollisionDetail("-1", "Sphere", "Bounds", "4", "30", "30", "32", "30", "30", "30");
}
