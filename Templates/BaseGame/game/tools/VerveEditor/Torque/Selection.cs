//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// Torque3D
//
//-----------------------------------------------------------------------------

function VTorque::GetSelectedCount()
{
    if ( !isObject( EWorldEditor ) )
    {
        // Null.
        return 0;
    }
    
    // Return Count.
    return EWorldEditor.getSelectionSize();
}

function VTorque::GetSelectedObject( %index )
{
    if ( !isObject( EWorldEditor ) )
    {
        // Null.
        return 0;
    }
    
    // Init Index.
    if ( %index $= "" )
    {
        %index = 0;
    }
    
    // Return Object.
    return EWorldEditor.getSelectedObject( %index );
}

function VTorque::SetSelectedObject( %object )
{
    if ( !isObject( EWorldEditor ) )
    {
        return;
    }
    
    EWorldEditor.selectObject( %object );
}