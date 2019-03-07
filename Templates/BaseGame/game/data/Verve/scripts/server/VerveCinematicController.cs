//-----------------------------------------------------------------------------
// Verve
// Copyright (C) 2014 - Violent Tulip
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

$Verve::CinematicController = 0;

//-----------------------------------------------------------------------------

function Verve::GetCinematicController()
{
    // Valid Controller?
    if ( !isObject( $Verve::CinematicController ) )
    {
        $Verve::CinematicController = new VController()
        {
            Class = "VerveCinematicController";
        };
    }

    // Return Controller.
    return $Verve::CinematicController;
}

//-----------------------------------------------------------------------------

// Verve::PlayCinematic( "sequences/BurgFlythrough.vsf" );
function Verve::PlayCinematic( %sequenceFile )
{
    if ( !isFile( %sequenceFile ) )
    {
        error ( "Verve::PlayCinematic() - Invalid Sequence File." );
        return 0;
    }

    // Fetch Controller.
    %controller = Verve::GetCinematicController();

    // Already Playing?
    if ( %controller.isPlaying() )
    {
        error ( "Verve::PlayCinematic() - Cinematic in Progress." );
        return 0;
    }

    // Load the Sequence.
    if ( !%controller.readFile( %sequenceFile ) )
    {
        return 0;
    }

    // Stop Input.
    if ( isObject( moveMap ) )
    {
        moveMap.pop();
    }

    // Store the Current Gui.
    $Verve::StoredGui = Canvas.getContent();
    
    // Valid GUI?
    if ( !isObject( VerveCinematicGui ) )
    {
        // Execute GUI Script.
        exec( "art/gui/VerveCinematic.gui" );
    }

    // Set the Cinematic Gui.
    Canvas.setContent( VerveCinematicGui );

    // Clear First Person.
    %clientCount = ClientGroup.getCount();
    for ( %i = 0; %i < %clientCount; %i++ )
    {
        // Fetch Client.
        %clientConnection = ClientGroup.getObject( %i );
        // Store Status.
        %clientConnection.FirstPerson = %clientConnection.isFirstPerson();
        // Clear.
        %clientConnection.setFirstPerson( false );
    }

    // Play the Sequence.
    %controller.play();

    // Return the Controller.
    return %controller;
}

//-----------------------------------------------------------------------------

function VerveCinematicController::onStop( %this )
{
    // Reset First Person Status.
    %clientCount = ClientGroup.getCount();
    for ( %i = 0; %i < %clientCount; %i++ )
    {
        // Fetch Client.
        %clientConnection = ClientGroup.getObject( %i );
        // Reset.
        %clientConnection.setFirstPerson( %clientConnection.FirstPerson );
    }

    // Reset the Canvas.
    Canvas.setContent( $Verve::StoredGui );

    // Resume Input.
    if ( isObject( moveMap ) )
    {
        moveMap.push();
    }
}