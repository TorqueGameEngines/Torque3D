//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VEditorScrollControl::onScroll( %this )
{
    %notifyObj = %this.getObject( 0 );
    if ( %notifyObj.isMethod( "onScroll" ) )
    {
        %notifyObj.onScroll();
    }
}

function VerveEditorScrollNotify::onWake( %this )
{
    VerveEditorScrollNotifyV::onWake( %this );
    VerveEditorScrollNotifyH::onWake( %this );
}

function VerveEditorScrollNotify::onScroll( %this )
{
    %this.onResize();
}

function VerveEditorScrollNotify::onResize( %this )
{
    VerveEditorScrollNotifyV::onResize( %this );
    VerveEditorScrollNotifyH::onResize( %this );
}

function VerveEditorScrollNotify::onParentResized( %this )
{
    %this.schedule( 32, "updateSize" );
}

function VerveEditorScrollNotify::updateSize( %this )
{
    VerveEditorScrollNotifyH::updateSize( %this );
    VerveEditorScrollNotifyV::updateSize( %this );
}

//-------------------------------------------------------------------------

function VerveEditorScrollNotifyV::onWake( %this )
{
    if ( !isObject( $VerveEditor::ScrollNotifyVSet ) )
    {
        $VerveEditor::ScrollNotifyVSet = new SimSet();
    }
    
    $VerveEditor::ScrollNotifyVSet.add( %this );
}

function VerveEditorScrollNotifyV::onScroll( %this )
{
    %this.onResize();
}

function VerveEditorScrollNotifyV::onResize( %this )
{
    if ( !isObject( $VerveEditor::ScrollNotifyVSet ) )
    {
        // Not Awake Yet!
        return;
    }
    
    %scrollPosition = %this.getParent().getScrollPositionY();
    if ( !%this.SurpressUpdate )
    {
        %refSet   = $VerveEditor::ScrollNotifyVSet;
        %refCount = %refSet.getCount();
        for ( %i = 0; %i < %refCount; %i++ )
        {
            %refObject = %refSet.getObject( %i ).getParent();
            %refObject.SurpressUpdate = true;
                %refObject.setScrollPosition( %refObject.getScrollPositionX(), %scrollPosition );
            %refObject.SurpressUpdate = false;
        }
    }
}

function VerveEditorScrollNotifyV::onParentResized( %this )
{
    %this.schedule( 32, "updateSize" );
}

function VerveEditorScrollNotifyV::updateSize( %this )
{
    %minX = getWord( %this.getObject( 0 ).MinExtent, 0 );
    %minY = getWord( %this.getParent().getExtent(), 1 ) - 3;
    %this.MinExtent = %minX SPC %minY;
    
    %newX = getWord( %this.getExtent(), 0 );
    %newY = getWord( VerveEditorTrackStack.getExtent(), 1 );
    %this.setExtent( %newX, %newY );
    
    // The onResize callback isn't called if all we did was move around
    %this.onResize();
}

//-------------------------------------------------------------------------

function VerveEditorScrollNotifyH::onWake( %this )
{
    if ( !isObject( $VerveEditor::ScrollNotifyHSet ) )
    {
        $VerveEditor::ScrollNotifyHSet = new SimSet();
    }
    
    $VerveEditor::ScrollNotifyHSet.add( %this );
}

function VerveEditorScrollNotifyH::onScroll( %this )
{
    %this.onResize();
}

function VerveEditorScrollNotifyH::onResize( %this )
{
    if ( !isObject( $VerveEditor::ScrollNotifyHSet ) )
    {
        // Not Awake Yet!
        return;
    }
    
    %scrollPosition = %this.getParent().getScrollPositionX();
    if ( !%this.SurpressUpdate )
    {
        %refSet   = $VerveEditor::ScrollNotifyHSet;
        %refCount = %refSet.getCount();
        for ( %i = 0; %i < %refCount; %i++ )
        {
            %refObject = %refSet.getObject( %i ).getParent();
            %refObject.SurpressUpdate = true;
                %refObject.setScrollPosition( %scrollPosition, %refObject.getScrollPositionY() );
            %refObject.SurpressUpdate = false;
        }
    }
}

function VerveEditorScrollNotifyH::onParentResized( %this )
{
    %this.schedule( 32, "updateSize" );
}

function VerveEditorScrollNotifyH::updateSize( %this )
{
    %this.MinExtent = %this.getObject( 0 ).MinExtent;
    %this.setExtent( getWord( %this.getParent().getExtent(), 0 ) - 19, getWord( %this.getExtent(), 1 ) );
    
    // The onResize callback isn't called if all we did was move around
    %this.onResize();
}