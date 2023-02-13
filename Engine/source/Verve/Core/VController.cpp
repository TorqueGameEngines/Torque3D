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
#include "Verve/Core/VController.h"
#include "Verve/Core/VObject.h"
#include "Verve/Core/VGroup.h"
#include "Verve/Core/VTrack.h"

#include "Verve/Extension/Director/VDirectorGroup.h"

#include "console/consoleObject.h"
#include "console/consoleTypes.h"
#include "math/mMathFn.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VController );
//-----------------------------------------------------------------------------

VController::VController( void ) :
        mStatus( ( k_StatusInit | k_StatusStopped ) ),
        mTime( 0 ),
        mLastTime( 0 ),
        mTimeScale( 1.f ),
        mDuration( 5000 ),
        mLoop( false ),
        mLoopBackwards( false ),
        mLoopCount( -1 ),
        mLoopIndex( 0 ),
        mLoopDelay( 0 ),
        mLoopDelayTime( 0 ),
        mJump( k_JumpInvalid ),
        mJumpTime( 0 ),
        mResetOnCompletion( true )
{
    // Don't Process Ticks.
    setProcessTicks( false );
}

VController::~VController( void )
{
    // Void.
}

void VController::initPersistFields()
{
   docsURL;
    addGroup( "Controller" );
        addProtectedField( "Time",      TypeS32,  Offset( mTime,              VController ), &setTime,      &defaultProtectedGetFn, "Current position of the Controller (in milliseconds)." );
        addProtectedField( "Duration",  TypeS32,  Offset( mDuration,          VController ), &setDuration,  &defaultProtectedGetFn, "Total length of the sequence (in milliseconds)." );
        addProtectedField( "TimeScale", TypeF32,  Offset( mTimeScale,         VController ), &setTimeScale, &defaultProtectedGetFn, "Speed of playback. A value > 0.0 will enable the Controller to play forwards, while a value < 0.0 will play backwards. If |TimeScale| > 1.0, then playback will be faster than normal, while |TimeScale| < 1.0 will be slower." );

        addField( "Loop",               TypeBool, Offset( mLoop,              VController ), "Instead of stopping once playback is complete, the Controller will reset and resume play." );
        addField( "LoopBackwards",      TypeBool, Offset( mLoopBackwards,     VController ), "When the sequence loops, reverse the direction of play." );
        addField( "LoopCount",          TypeS32,  Offset( mLoopCount,         VController ), "The number of times the sequence loops before stopping. -1 will cause the sequence to loop indefinitely." );
        addField( "LoopDelay",          TypeS32,  Offset( mLoopDelay,         VController ), "When the sequence loops, delay playback by this value (in milliseconds)." );

        addField( "ResetOnCompletion",  TypeBool, Offset( mResetOnCompletion, VController ), "When the sequence is completed, reset the state of the Controller." );
    endGroup( "Controller" );

    // Parent Call.
    Parent::initPersistFields();
}

//-----------------------------------------------------------------------------
//
// ITickable Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VController::processTick();
// 
// This method controls the playback of the entire sequence. It integrates all
// of the groups and handles sequence looping and jumping.
// 
//-----------------------------------------------------------------------------
void VController::processTick( void )
{
    if ( mTimeScale == 0.f )
    {
        // Pause.
        pause();

        // Exit.
        return;
    }

    // Calculate Delta.
    const S32 time  = Sim::getCurrentTime();
    S32 delta = ( time - mLastTime );
    mLastTime = time;

    // Reverse?
    if ( mTimeScale < 0.f )
    {
        // Negative Delta.
        delta *= -1;
    }

    if ( mLoopDelayTime > 0 )
    {
        // Update Delay Time.
        mLoopDelayTime -= getMin( mAbs( delta ), mLoopDelayTime );

        // Exit.
        return;
    }

    // Jump Delta?
    if ( mJump == k_JumpDelta )
    {
        // Jump.
        delta = mJumpTime;

        // Clear.
        mJump     = k_JumpInvalid;
        mJumpTime = 0;
    }

    if ( ( isPlayingForward()  && ( mTime + delta ) > mDuration )
         || ( !isPlayingForward() && ( mTime + delta ) < 0 ) )
    {
        // Clamp Delta.
        delta = ( ( mTimeScale > 0.f ) * mDuration ) - mTime;

        // Note: If we are playing forwards, we're at the end of the
        //       sequence and we want to loop/reset the Controller, then we
        //       need to handle that now.
        if ( delta == 0 )
        {
            onPostTick();
        }
    }

    // Valid Delta?
    if ( delta == 0 )
    {
        // Exit.
        return;
    }

    // Trigger Update.
    mControllerUpdateSignal.trigger( mTime, delta );

    // Update Time.
    mTime += delta;

    // Perform Post Tick.
    onPostTick();
}

//-----------------------------------------------------------------------------
// 
// VController::onPostTick();
// 
// This method is called onces a tick has been processed. It will perform the
// the right checks to see if the Controller has finished playing. It also 
// handles special cases like Looping or Resetting the Controller.
// 
//-----------------------------------------------------------------------------
void VController::onPostTick( void )
{
    // Jump Time?
    if ( mJump == k_JumpTime )
    {
        // Jump Post Update.
        reset( mJumpTime );

        // Clear.
        mJump     = k_JumpInvalid;
        mJumpTime = 0;
    }

    // Sequence Completed?
    if ( isPlayingForward() && mTime >= mDuration 
        || !isPlayingForward() && mTime <= 0 )
    {
        bool stopPlaying = true;
        if ( mLoop )
        {
            // Don't Stop.
            stopPlaying = false;

            if ( mLoopBackwards )
            {
                // Change Direction.
                setTimeScale( -1.f * mTimeScale );
            }
            else
            {
                // Reset Time.
                reset();
            }

            if ( mLoopDelay > 0 )
            {
                // Resume After Delay.
                mLoopDelayTime = mLoopDelay;
            }

            // At the Start of the Sequence?
            if ( mTime <= 0 && mLoopCount >= 0 )
            {
                // Stop Looping?
                stopPlaying = ( ++mLoopIndex >= mLoopCount );
            }

            // Callback.
            Con::executef( this, "onLoop" );

            // Loop Signal.
            postEvent( k_EventLoop );
        }

        // Stop?
        if ( stopPlaying )
        {
            // Stop Only.
            stop( mResetOnCompletion );
        }
    }
}

//-----------------------------------------------------------------------------
//
// Controller Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VController::reset();
// 
// Reset the Controller to the start of the sequence.
// 
//-----------------------------------------------------------------------------
void VController::reset( void )
{
    // Reset.
    reset( ( isPlayingForward() ) ? 0 : mDuration );
}

//-----------------------------------------------------------------------------
// 
// VController::reset( pTime );
// 
// Reset the Controller to the target time. This is a very important method as
// it allows tracks and events to reset their state as well as prepare
// themselves for playback.
// 
//-----------------------------------------------------------------------------
void VController::reset( const S32 &pTime )
{
    // Reset Time.
    mTime     = pTime;
    mLastTime = Sim::getCurrentTime();

    // Reset Delay Time.
    mLoopDelayTime = 0;

    // Post Event.
    postEvent( k_EventReset );
}

//-----------------------------------------------------------------------------
// 
// VController::play();
// 
// Start playing the sequence from the current time and execute a number of
// callbacks.
// 
//-----------------------------------------------------------------------------
void VController::play( void )
{
    if ( isPlaying() || mTime < 0 || mTime > mDuration )
    {
        // Sanity!
        return;
    }

    // Reset Time.
    mLastTime = Sim::getCurrentTime();

    // Start Updating.
    setProcessTicks( true );

    if ( mStatus & k_StatusInit )
    {
        // Init Signal.
        postEvent( k_EventInit );

        // Clear Init Status.
        mStatus &= ~k_StatusInit;
    }

    // Update Status.
    updateStatus( k_StatusPlaying );

    // Play Signal.
    postEvent( k_EventPlay );

    // Callback.
    Con::executef( this, "onPlay" );
}

//-----------------------------------------------------------------------------
// 
// VController::play( pTime );
// 
// Start playing the sequence from the desired time.
// 
//-----------------------------------------------------------------------------
void VController::play( const S32 &pTime )
{
    // Reset.
    reset( pTime );

    // Play.
    play();
}

//-----------------------------------------------------------------------------
// 
// VController::pause();
// 
// Cease playback of the sequence, but maintain the current time.
// 
//-----------------------------------------------------------------------------
void VController::pause( void )
{
    // Stop Updating.
    setProcessTicks( false );

    // Update Status.
    updateStatus( k_StatusPaused );

    // Pause Signal.
    postEvent( k_EventPause );

    // Callback.
    Con::executef( this, "onPause" );
}

//-----------------------------------------------------------------------------
// 
// VController::stop( pReset );
// 
// Stop playback altogether and reset the Controller to the start of the
// sequence.
// 
//-----------------------------------------------------------------------------
void VController::stop( const bool &pReset )
{
    // Stop Updating.
    setProcessTicks( false );

    // Reset Loop Index.
    mLoopIndex = 0;

    // Update Status.
    updateStatus( ( k_StatusInit | k_StatusStopped ) );

    // Reset?
    if ( pReset )
    {
        // Reset.
        reset();
    }

    // Stop Signal.
    postEvent( k_EventStop );

    // Callback.
    Con::executef( this, "onStop" );
}

//-----------------------------------------------------------------------------
// 
// VController::jump();
// 
// Jump the Controller time forward 1 tick (32ms).
// 
//-----------------------------------------------------------------------------
void VController::jump( void )
{
    // Jump 1 tick.
    jump( k_JumpDelta, ( isPlayingForward() ) ? TickMs : -TickMs );
}

//-----------------------------------------------------------------------------
// 
// VController::jump( pType, pDelta );
// 
// Jump the Controller time by the target Delta.
// 
//-----------------------------------------------------------------------------
void VController::jump( const eControllerJumpType &pType, const S32 &pDelta )
{
    // Jump.
    mJump     = pType;
    mJumpTime = pDelta;
}

//-----------------------------------------------------------------------------
// 
// VController::updateStatus( pStatus );
// 
// Clear the regular playback states and add the updated state.
// 
//-----------------------------------------------------------------------------
void VController::updateStatus( const S32 &pStatus )
{
    // Clear Playback Status.
    mStatus &= ~( k_StatusPlaying | k_StatusPaused | k_StatusStopped );

    // Add New Status.
    mStatus |= pStatus;
}

//-----------------------------------------------------------------------------
//
// Reference Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VController::getObject( pLabel );
// 
// Returns the group with the given name. If no group belongs to the Controller
// with that name, then a NULL value is returned.
// 
//-----------------------------------------------------------------------------
VGroup *VController::getObject( const String &pLabel )
{
    VGroup *node = ( VGroup* )mChildNode;
    while ( node )
    {
        // Compare Names.
        if ( node->getLabel().equal( pLabel, String::NoCase ) )
        {
            // Valid.
            return node;
        }

        // Next Sibling.
        node = ( VGroup* )node->mSiblingNextNode;
    }

    // Invalid.
    return NULL;
}

//-----------------------------------------------------------------------------
// 
// VController::getDirectorGroup();
// 
// Returns the DirectorGroup reference if the Controller has a one.
// 
//-----------------------------------------------------------------------------
VDirectorGroup *VController::getDirectorGroup( void )
{
    for ( ITreeNode *node = mChildNode; node != NULL; node = node->mSiblingNextNode )
    {
        if ( VDirectorGroup *group = dynamic_cast<VDirectorGroup*>( node ) )
        {
            // Return Group.
            return group;
        }
    }

    // Invalid Group.
    return NULL;
}

//-----------------------------------------------------------------------------
// 
// VController::getDirectorTrack();
// 
// Returns the DirectorTrack reference if the DirectorGroup has one.
// 
//-----------------------------------------------------------------------------
VDirectorTrack *VController::getDirectorTrack( void )
{
    VDirectorGroup *group = getDirectorGroup();
    if ( !group )
    {
        // Invalid Track.
        return NULL;
    }

    // Return Track.
    return group->getDirectorTrack();
}

//-----------------------------------------------------------------------------
// 
// VController::getDataValue( pFieldName, *pValue );
// 
// Returns true if the field is a DataTable member and can be correctly
// evaluated. If this is the case, then pValue will contain the result.
// 
//-----------------------------------------------------------------------------
bool VController::getDataValue( const String &pFieldName, String &pValue )
{
    return mDataTable.getValue( this, pFieldName, pValue );
}

//-----------------------------------------------------------------------------
// 
// VController::clearData();
// 
// Clear the contents of the DataTable entirely.
// 
//-----------------------------------------------------------------------------
void VController::clearData( void )
{
    while ( mDataTable.getCount() > 0 )
    {
        // Clear Item.
        clearData( 0 );
    }
}

//-----------------------------------------------------------------------------
// 
// VController::clearData( pIndex );
// 
// Clear the DataTable entry with the given index.
// 
//-----------------------------------------------------------------------------
void VController::clearData( const S32 &pIndex )
{
    VDataTable::sDataItem data;
    if ( mDataTable.getItem( pIndex, &data ) )
    {
        // Clear Data.
        clearData( data.FieldName );
    }
}

//-----------------------------------------------------------------------------
// 
// VController::clearData( pIndex );
// 
// Clear the DataTable entry with the given field name.
// 
//-----------------------------------------------------------------------------
void VController::clearData( const String &pFieldName )
{
    // Clear Dynamic Field.
    setDataField( pFieldName, NULL, "" );

    // Clear Item.
    mDataTable.clear( pFieldName );
}

//-----------------------------------------------------------------------------
// 
// VController::sort();
// 
// Sort each track in each of the child groups.
// 
//-----------------------------------------------------------------------------
void VController::sort( void )
{
    for ( ITreeNode *group = mChildNode; group != NULL; group = group->mSiblingNextNode )
    {
        for ( ITreeNode *track = group->mChildNode; track != NULL; track = track->mSiblingNextNode )
        {
            // Sort Track.
            ( ( VTrack* )track )->sort();
        }
    }
}

//-----------------------------------------------------------------------------
//
// Write Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VController::writeDataTable( pElement );
// 
// Write the DataTable out to a TinyXML document.
// 
//-----------------------------------------------------------------------------
bool VController::writeDataTable( tinyxml2::XMLElement *pElement )
{
    // Create Data Table Root.
    tinyxml2::XMLElement *dataTableRoot = pElement->GetDocument()->NewElement( "DataTable" );
    pElement->LinkEndChild( dataTableRoot );

    for ( VDataTable::VDataMap::Iterator itr = mDataTable.mDataMap.begin(); itr != mDataTable.mDataMap.end(); ++itr )
    {
        // Fetch Data.
        VDataTable::sDataItem *data = &itr->value;

        // Create Element.
        tinyxml2::XMLElement* dataElement = pElement->GetDocument()->NewElement( "DataItem" );

        // Apply Attributes.
        dataElement->SetAttribute( "Type",  VDataTable::getDataTypeDescription( data->Type ) );
        dataElement->SetAttribute( "Name",  data->FieldName.c_str() );
        dataElement->SetAttribute( "Value", getDataField( StringTable->insert( data->FieldName.c_str() ), NULL ) );

        // Add.
        dataTableRoot->LinkEndChild( dataElement );
    }

    return true;
}

//-----------------------------------------------------------------------------
//
// Read Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VController::readDataTable( pElement );
// 
// Read the DataTable from a TinyXML document.
// 
//-----------------------------------------------------------------------------
bool VController::readDataTable( tinyxml2::XMLElement *pElement )
{
    tinyxml2::XMLElement *dataTableRoot = pElement->FirstChildElement( "DataTable" );
    if ( dataTableRoot )
    {
        for ( tinyxml2::XMLElement *child = dataTableRoot->FirstChildElement(); child != NULL; child = child->NextSiblingElement() )
        {
            // Get Field Data.
            const char *fieldType  = child->Attribute( "Type" );
            const char *fieldName  = child->Attribute( "Name" );
            const char *fieldValue = child->Attribute( "Value" );

            // Add Data Item.
            mDataTable.insert( VDataTable::getDataTypeEnum( fieldType ), fieldName );

            // Set Field Value.
            setDataField( StringTable->insert( fieldName ), NULL, fieldValue );
        }
    }
    
    // Valid Read.
    return true;
}

//-----------------------------------------------------------------------------
//
// Property Methods.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VController::postEvent( pEvent );
// 
// Process an event signal to all event subscribers. This method is used to
// signal changes in the Controller's status.
// 
// For a full list of possible events, see the 'eControllerEventType'
// declaration in VController.h.
// 
//-----------------------------------------------------------------------------
void VController::postEvent( const eControllerEventType &pEvent )
{
    // Signal Event.
    mControllerEventSignal.trigger( pEvent );
}

//-----------------------------------------------------------------------------
// 
// VController::setTimeScale( pTimeScale );
// 
// Set the speed of playback. In effect, a value of 0.5 will double the real
// time taken to complete the playback of the sequence, while a value of 2.0
// will halve the time needed.
// 
//-----------------------------------------------------------------------------
void VController::setTimeScale( const F32 &pTimeScale )
{
    // Need an Update?
    const bool update = ( pTimeScale != 0.f && ( mTimeScale == 0.f || ( ( mTimeScale > 0.f ) != ( pTimeScale > 0.f ) ) ) );

    // Store.
    mTimeScale = pTimeScale;

    // Update $timeScale Variable.
    Con::setFloatVariable( "timeScale", mFabs( mTimeScale ) );

    if ( update )
    {
        // Reset.
        reset( mTime );
    }
}

//-----------------------------------------------------------------------------
//
// Console Methods.
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VController, readFile, bool, (String fileName), (""), "( string pFileName ) - Clears the object and loads the new data from the given filename.\n"
                                                  "@param pFileName The target file to read from.\n"
                                                  "@return Returns true if the read was successful." )
{
    // Clear Sequence Lists.
    object->clear();

    // Clear Data Table.
    object->clearData();

    // Read Target File.
    if ( !VPersistence::readFile( fileName, object ) )
    {
        // Re-Clear.
        object->clear();

        // Invalid Read.
        return false;
    }

    // Initial Sort.
    object->sort();

    // Reset.
    object->reset();

    // Valid Read.
    return true;
}

DefineEngineMethod( VController, clear, void, (), , "( void ) - Detaches and deletes all of the child objects.\n"
                                               "@return No return value." )
{
    // Clear Sequence Lists.
    object->clear();

    // Clear Data Table.
    object->clearData();
}

DefineEngineMethod( VController, reset, void, (S32 time), (-1), "( [int pTime] ) - Reset the Controller's and child object's state.\n"
                                               "@param pTime The target time to reset to.\n"
                                               "@return No return value." )
{
   if (time != -1)
   {
      // Reset Sequence.
      object->reset(time);
      return;
   }

    // Default Reset.
    object->reset();
}

DefineEngineMethod( VController, isPlaying, bool, (), , "( void ) - Is the sequence currently playing?\n"
                                                   "@return Returns true if the Controller is playing." )
{
    // Is Playing?
    return ( object->isPlaying() );
}

DefineEngineMethod( VController, play, void, (S32 time), (-1), "( [int pTime] ) - Play the sequence. If a value for pTime is specified, the Controller is reset and played from that time.\n"
                                              "@param pTime The time to start playing the sequence from.\n"
                                              "@return No return value." )
{
    S32 startTime = object->getTime();
    if (time != -1)
    {
        startTime = time;
    }

    // Play From Specified Time.
    object->play( startTime );
}

DefineEngineMethod( VController, step, void, (),, "( void ) - Step forward one frame.\n"
                                              "@return No return value." )
{
    if ( object->isPlaying() )
    {
        // Sanity!
        return;
    }

    // Play.
    object->play( object->getTime() );

    // Jump.
    object->jump();

    // Step Forward One Frame.
    object->processTick();

    // Stop.
    object->stop( false );
}

DefineEngineMethod( VController, isPaused, bool, (), , "( void ) - Is the sequence currently paused?\n"
                                                  "@return Returns true if the Controller is paused." )
{
    // Is Paused?
    return ( object->isPaused() );
}

DefineEngineMethod( VController, pause, void, (), , "( void ) - Pause the sequence. Playback can resume by calling VController::play().\n"
                                               "@return No return value." )
{
    // Pause Sequence.
    object->pause();
}

DefineEngineMethod( VController, isStopped, bool, (), , "( void ) - Is the sequence currently stopped?\n"
                                                   "@return Returns true if the Controller is stopped." )
{
    // Is Stopped?
    return ( object->isStopped() );
}

DefineEngineMethod( VController, stop, void, (bool reset), (true), "( [bool pReset] ) - Stop the sequence and optionally reset it.\n"
                                              "@param pReset Reset the Controller after stopping.\n"
                                              "@return No return value." )
{
    // Stop Sequence.
    object->stop(reset);
}

DefineEngineMethod( VController, getTimeScale, F32, (), , "( void ) - Get the playback speed. A value > 0.0 will enable the Controller to play forwards, while a value < 0.0 will play backwards.\n"
                                                     "@return Playback Speed." )
{
    // Get Time Scale.
    return object->getTimeScale();
}

DefineEngineMethod( VController, setTimeScale, void, (float timeScale), (1), "( float pTimeScale ) - Set the playback speed. A value > 0.0 will enable the Controller to play forwards, while a value < 0.0 will play backwards. If |pTimeScale| > 1.0, then playback will be faster than normal, while |pTimeScale| < 1.0 will be slower.\n"
                                                      "@param pTimeScale Playback speed.\n"
                                                      "@return No return value." )
{
    // Set Time Scale.
    object->setTimeScale(timeScale);
}

DefineEngineMethod( VController, isDataField, bool, (String fieldName), (""), "( string pFieldName ) - Is the field a member of the Data Table?\n"
                                                     "@param pFieldName The name of the dynamic field you wish to check.\n"
                                                     "@return Returns true if the field is a member of the Data Table." )
{
    if (fieldName.isEmpty())
    {
        return false;
    }

    // Is Field.
    return object->getDataTable().getItem(fieldName);
}

DefineEngineMethod( VController, getDataFieldCount, S32, (), , "( void ) - Get the number of data elements in the Data Table.\n"
                                                          "@return Returns the size of the Data Table." )
{
    // Return Count.
    return object->getDataTable().getCount();
}

DefineEngineMethod( VController, getDataFieldName, const char *, (S32 index), (0), "( int pIndex ) - Get the name of the field given by the passed index.\n"
                                                                  "@param pIndex The index of the data field you wish to check.\n"
                                                                  "@return Returns the name of the field corresponding to the given index." )
{
    VDataTable::sDataItem data;
    if ( !object->getDataTable().getItem(index, &data ) || data.Type == VDataTable::k_TypeInvalid )
    {
        // Invalid Field.
        return "";
    }

    // Return Field Name.
    return data.FieldName;
}

DefineEngineMethod( VController, getDataFieldValue, const char *, (String fieldName), (""), "( string pFieldName ) - Get the evaluated data from the data field.\n"
                                                                   "@param pFieldName The name of the field you wish to evaluate.\n"
                                                                   "@return Returns the evaluated data from the field." )
{
    String fieldValue;
    if ( object->getDataValue(fieldName, fieldValue ) )
    {
        // Create Buffer.
        char *buffer = Con::getReturnBuffer( 256 );
        dStrcpy( buffer, fieldValue.c_str(), 256 );

        // Return Value.
        return buffer;
    }

    // Return NULL.
    return "0";
}

DefineEngineMethod( VController, getDataFieldType, const char *, (String fieldName), (""), "( string pFieldName ) - Get the type of data for the given field.\n"
                                                                  "@param pFieldName The name of the field you wish to check.\n"
                                                                  "@return Returns the data type." )
{
    VDataTable::sDataItem data;
    if ( !object->getDataTable().getItem(fieldName, &data ) || data.Type == VDataTable::k_TypeInvalid )
    {
        // Invalid Field.
        return "";
    }

    // Return Field Type.
    return VDataTable::getDataTypeDescription( data.Type );
}

#ifdef VT_EDITOR
//-----------------------------------------------------------------------------
//
// Debug Methods.
//
//-----------------------------------------------------------------------------

DefineEngineMethod( VController, writeFile, bool, (String fileName), (""), "( string pFileName ) - Save to a given filename.\n"
                                                   "@param pFileName The target file to write to.\n"
                                                   "@return Returns true if the write was successful." )
{
    // Write Target File.
    return VPersistence::writeFile(fileName.c_str(), object );
}

DefineEngineMethod( VController, readTemplate, bool, (String fileName), (""), "( string pFileName ) - Load data from given filename.\n"
                                                      "@param pFileName The target file to read from.\n"
                                                      "@return Returns true if the read was successful." )
{
    // Read Target File.
    return VPersistence::readFile(fileName.c_str(), object );
}

DefineEngineMethod( VController, getCount, S32, (),, "( void ) - Get the number of child objects.\n"
                                                 "@return Returns the number of child objects." )
{
    // Size.
    return object->size();
}

DefineEngineMethod( VController, getObject, S32, (S32 index), (0), "( int pIndex ) - Get the object corresponding to the given index.\n"
                                                  "@param pIndex The index of the object you wish to retrieve.\n"
                                                  "@return Returns the SimObjectID for the object." )
{
    // Fetch Object.
    VObject *objectRef  = ( VObject* )object->at(index);

    // Return Group ID.
    return ( objectRef ) ? objectRef->getId() : 0;
}

DefineEngineMethod( VController, addObject, void, (SimObject* simObj), (nullAsType<SimObject*>()), "( SimObject pObject ) - Add a child object to this node.\n"
                                                   "@param pObject The SimObjectID of the object to be added to this node.\n"
                                                   "@return No return value." )
{
   if (simObj == nullptr)
      return;

    VObject *child = dynamic_cast<VObject*>(simObj);
    if ( child )
    {
        // Add Child.
        child->addTo( object );
    }
}

DefineEngineMethod( VController, removeObject, void, (SimObject* simObj), (nullAsType<SimObject*>()), "( SimObject pObject ) - Remove the target object from this node.\n"
                                                      "@param pObject The SimObjectID of the object to be removed from this node.\n"
                                                      "@return No return value." )
{
   if (simObj == nullptr)
      return;

    VObject *child = dynamic_cast<VObject*>(simObj);
    if ( child && child->getParent() == object )
    {
        child->remove();
    }
}

DefineEngineMethod( VController, sortGroups, void, (),, "( void ) - Sort Groups by their Labels.\n"
                                                    "@return No return value." )
{
    // Ensure that the Director Group is the First Group.
    VDirectorGroup *directorGroup = object->getDirectorGroup();
    if ( directorGroup && directorGroup != object->mChildNode )
    {
        // Detach.
        directorGroup->remove();

        // Add to the Front of the Controller.
        directorGroup->addToFront( object );
    }

    const S32 count = object->size();
    for ( S32 j = 0; j < count; j++ )
    {
        ITreeNode *node = object->mChildNode;
        if ( dynamic_cast<VDirectorGroup*>( node ) != NULL )
        {
            // Skip Director Group.
            node = node->mSiblingNextNode;
        }

        for ( ; node != NULL; node = node->mSiblingNextNode )
        {
            VGroup *groupA = ( VGroup* )node;
            VGroup *groupB = ( VGroup* )node->mSiblingNextNode;
            if ( !groupB )
            {
                // No Node.
                break;
            }

            // Swap?
            if ( groupA->getLabel().compare(groupB->getLabel()) > 0 )
            {
                // Get Outer Siblings.
                ITreeNode *prevNode = groupA->mSiblingPrevNode;
                ITreeNode *nextNode = groupB->mSiblingNextNode;
                
                if ( groupA->mParentNode && groupA->mParentNode->mChildNode == groupA )
                {
                    // New Child Node.
                    groupA->mParentNode->mChildNode = groupB;
                }

                //
                // Move A.

                groupA->mSiblingPrevNode = groupB;
                groupA->mSiblingNextNode = nextNode;

                if ( nextNode )
                {
                    // Update Outer Sibling.
                    nextNode->mSiblingPrevNode = groupA;
                }

                //
                // Move B.

                groupB->mSiblingPrevNode = prevNode;
                groupB->mSiblingNextNode = groupA;

                if ( prevNode )
                {
                    // Update Outer Sibling.
                    prevNode->mSiblingNextNode = groupB;
                }
            }
        }
    }
}

DefineEngineMethod( VController, sortTracks, void, (),, "( void ) - Sort Tracks by their Labels.\n"
                                                    "@return No return value." )
{
    for ( ITreeNode *group = object->mChildNode; group != NULL; group = group->mSiblingNextNode )
    {
        const S32 count = ( ( VGroup* )group )->size();
        for ( S32 j = 0; j < count; j++ )
        {
            for ( ITreeNode *node = group->mChildNode; node != NULL; node = node->mSiblingNextNode )
            {
                VTrack *trackA = ( VTrack* )node;
                VTrack *trackB = ( VTrack* )node->mSiblingNextNode;
                if ( !trackB )
                {
                    // No Node.
                    break;
                }

                // Swap?
                if ( trackA->getLabel().compare(trackB->getLabel()) > 0 )
                {
                    // Get Outer Siblings.
                    ITreeNode *prevNode = trackA->mSiblingPrevNode;
                    ITreeNode *nextNode = trackB->mSiblingNextNode;
                    
                    if ( trackA->mParentNode && trackA->mParentNode->mChildNode == trackA )
                    {
                        // New Child Node.
                        trackA->mParentNode->mChildNode = trackB;
                    }

                    //
                    // Move A.

                    trackA->mSiblingPrevNode = trackB;
                    trackA->mSiblingNextNode = nextNode;

                    if ( nextNode )
                    {
                        // Update Outer Sibling.
                        nextNode->mSiblingPrevNode = trackA;
                    }

                    //
                    // Move B.

                    trackB->mSiblingPrevNode = prevNode;
                    trackB->mSiblingNextNode = trackA;

                    if ( prevNode )
                    {
                        // Update Outer Sibling.
                        prevNode->mSiblingNextNode = trackB;
                    }
                }
            }
        }
    }
}

DefineEngineMethod( VController, addDataField, void, (String fieldType, String fieldName), ("", ""), "( string pFieldType, string pFieldName ) - Add a new data entry to the Data Table.\n"
                                                      "@param pFieldType The method of evaluating the field's data.\n"
                                                      "@param pFieldName The name of the field to be added to the Data Table.\n"
                                                      "@return No return value." )
{
    // Insert Data.
    object->getDataTable().insert( VDataTable::getDataTypeEnum(fieldType), fieldName);
}

DefineEngineMethod( VController, removeDataField, void, (String fieldName), (""), "( string pFieldName ) - Remove a data entry from the Data Table.\n"
                                                         "@param pFieldName The name of the field to be removed from the Data Table.\n"
                                                         "@return No return value." )
{
    // Clear Data Item.
    object->clearData(fieldName);
}
#endif
