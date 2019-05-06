//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VEditorPropertyList::onAdd( %this )
{
    if ( !VEditorObjectPropertySet.isMember( %this ) )
    {
        // Add Reference List.
        VEditorObjectPropertySet.add( %this );
    }
}

function VEditorPropertyList::onRemove( %this )
{
    if ( isObject( %this.ControlCache ) )
    {
        if ( %this.ControlCache.getClassName() !$= "SimSet" )
        {
            // Clear Set.
            while ( %this.ControlCache.getCount() > 0 )
            {
                // Delete Control.
                %this.ControlCache.getObject( 0 ).delete();
            }
        }
        
        // Delete Cache.
        %this.ControlCache.delete();
    }
}

new ScriptGroup( VEditorObjectPropertySet )
{
    //-------------------------------------------------------------------------
    //
    // VObject
    //
    //-------------------------------------------------------------------------
    
    new ScriptObject( VObjectPropertyList )
    {
        SuperClass  = "VEditorPropertyList";
        
        Group[0]    = "VObject";
        Field[0, 0] = "Label";
        Field[0, 1] = "Enabled";
    };
};
