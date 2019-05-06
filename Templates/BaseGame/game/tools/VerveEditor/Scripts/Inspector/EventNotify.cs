//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::GetEventManager()
{
    if ( !isObject( $VerveEditor::EventManager ) )
    {
        $VerveEditor::EventManager = new EventManager()
        {
            Queue = "ProjectEventManager";
        };
    }

    return $VerveEditor::EventManager;
}

function VerveEditor::RegisterEvent( %eventName )
{
    if ( !VerveEditor::GetEventManager().isRegisteredEvent( %eventName ) )
    {
        // Register Event.
        VerveEditor::GetEventManager().RegisterEvent( %eventName );
    }
}

function VerveEditor::AddEventNotify( %object, %eventName, %callback )
{
    if ( isObject( $VerveEditor::EventManager ) )
    {
        // Subscribe To Event.
        $VerveEditor::EventManager.SubScribe( %object, %eventName, %callback );
    }
}

function VerveEditor::RemoveEventNotify( %object, %eventName )
{
    if ( isObject( $VerveEditor::EventManager ) )
    {
        // Remove Event.
        $VerveEditor::EventManager.Remove( %object, %eventName );
    }
}

function VerveEditor::PostEvent( %eventName, %refObject )
{
    if ( isObject( $VerveEditor::EventManager ) )
    {
        // Notify Event.
        $VerveEditor::EventManager.PostEvent( %eventName, %refObject );
    }
}