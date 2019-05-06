//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
// Class
//
//-----------------------------------------------------------------------------

function SimObject::isMemberOfClassList( %this, %typeList )
{
    %typeCount = getWordCount( %typeList );
    for ( %i = 0; %i < %typeCount; %i++ )
    {
        if ( %this.isMemberOfClass( getWord( %typeList, %i ) ) )
        {
            return true;
        }
    }
    
    return false;
}

//-----------------------------------------------------------------------------
//
// GUI
//
//-----------------------------------------------------------------------------

function GuiControl::getParentOfType( %this, %className )
{
    %parent = %this.getParent();
    while ( isObject( %parent ) )
    {
        if ( %parent.isMemberOfClass( %className ) )
        {
            return %parent;
        }

        %parent = %parent.getParent();
    }

    return 0;
}

//-----------------------------------------------------------------------------
//
// MATH
//
//-----------------------------------------------------------------------------

function mRound( %number, %delta )
{
    return ( mFloor( %number / %delta + 0.5 ) * %delta );
}

//-----------------------------------------------------------------------------
//
// STRING
//
//-----------------------------------------------------------------------------

function isWordInList( %word, %list )
{
    %wordCount = getWordCount( %list );
    for ( %i = 0; %i < %wordCount; %i++ )
    {
        if ( getWord( %list, %i ) $= %word )
        {
            return true;
        }
    }
    
    return false;
}

function sortWordList( %list )
{
   %wordCount = getWordCount( %list );
   for ( %j = 0; %j < %wordCount; %j++ )
   {
      for ( %i = %wordCount - 1; %i > %j; %i-- )
      {
         %wordA = getWord( %list, %i - 0 );
         %wordB = getWord( %list, %i - 1 );
         
         // Compare and swap if needed
         if ( strcmp( strlwr( %wordA ), strlwr( %wordB ) ) < 0 )
         {
            %list = setWord( %list, %i - 1, %wordA );
            %list = setWord( %list, %i - 0, %wordB );
         }
      }
   }
   
   return %list;
}