//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVShapeAnimationEnumField( %fieldContainer, %fieldName )
{
    // Create Enum Menu.
    return VerveEditor::CreateEnumField( %fieldContainer, %fieldName, "VEditorVShapeAnimationEnumPropertyField" );
}

function VEditorVShapeAnimationEnumPropertyField::OnWake( %this )
{
    // Clear List.
    %this.clear();
    
    // Valid Target?
    if ( !$VerveEditor::InspectorObject.isMethod( "getSceneObject" ) )
    {
        return;
    }
    
    // Fetch Scene Object.
    %objectReference = $VerveEditor::InspectorObject.getSceneObject();
    
    // Valid Object?
    if ( !isObject( %objectReference ) || !%objectReference.isMemberOfClass( "ShapeBase" ) )
    {
        return;
    }
    
    // Find the Constructor for this Shape.
    %objectConstructor = %this.FindConstructor( %objectReference );
    if ( !isObject( %objectConstructor ) )
    {
        // Invalid Shape Constructor.
        return;
    }
    
    // Iterate Over Sequences.
    %sequenceCount = %objectConstructor.getSequenceCount();
    for ( %i = 0; %i < %sequenceCount; %i++ )
    {
        %sequenceName = %objectConstructor.getSequenceName( %i );
        if ( %this.FindText( %sequenceName ) == -1 )
        {
            // Add Item.
            %this.add( %sequenceName, %this.Size() );
        }
    }
    
    // Sort.
    %this.sort();
}

function VEditorVShapeAnimationEnumPropertyField::FindConstructor( %this, %objectReference )
{
    %datablock = %objectReference.getDataBlock();
    if ( !isObject( %datablock ) )
    {
        return 0;
    }
    
    // Fetch the Shape File.
    %shapeFile = %datablock.shapeFile;
    
    %count = TSShapeConstructorGroup.getCount();
    for ( %i = 0; %i < %count; %i++ )
    {
        %obj = TSShapeConstructorGroup.getObject(%i);
        if ( %obj.baseShape $= %shapeFile )
        {
            return %obj;
        }
    }
    
    return 0;
}