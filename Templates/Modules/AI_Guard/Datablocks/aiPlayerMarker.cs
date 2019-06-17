//The AIPlayer marker is placed in the map during edit mode. When the map is loaded the
//marker is replaced by a guard player. (Assuming that the $AI_GUARD_ENABLED variable is set
//to true.) The marker is hidden or not depending on the value set in $AI_GUARD_MARKER_HIDE.
//The AIPlayer marker can use a dynamic variable - set during map creation - called 'respawn'
//Creating and setting the 'respawn' variable will override the default value set in
//$AI_GUARD_DEFAULTRESPAWN. This allows more freedom in determining which bots respawn and which do not.

datablock StaticShapeData(AIPlayerMarker)
{
   // Mission editor category, this datablock will show up in the
   // specified category under the "shapes" root category.
   category = "AIMarker";

   // Basic Item properties
   shapeFile = "data/Soldier/Shapes/soldier_Rigged.DAE";//"art/shapes/actors/Soldier/soldier_rigged.DAE";
};