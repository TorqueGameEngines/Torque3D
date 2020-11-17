//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

singleton GuiControlProfile( VEditorDefaultProfile )
{
    opaque        = true;
    fillColor     = "70 70 70";
    fillColorHL   = "90 90 90";
    fillColorNA   = "70 70 70";
    
    border        = 1;
    borderColor   = "120 120 120";
    borderColorHL = "100 100 100";
    borderColorNA = "240 240 240";

    fontType      = "Arial";
    fontSize      = 12;
    fontCharset   = ANSI;

    fontColor     = "255 255 255";
    fontColorHL   = "255 255 255";
    fontColorNA   = "255 255 255";
    fontColorSEL  = "255 255 255";
};

singleton GuiControlProfile( VEditorTestProfile )
{
    opaque        = true;
    fillColor     = "255 255 0";
    fillColorHL   = "255 255 0";
    fillColorNA   = "255 255 0";
};

singleton GuiControlProfile( VEditorNoFillProfile : VEditorDefaultProfile )
{
    opaque = false;
};

singleton GuiControlProfile( VEditorNoBorderProfile : VEditorDefaultProfile )
{
    border = false;
};

singleton GuiControlProfile( VEditorTransparentProfile : VEditorDefaultProfile )
{
    opaque = false;
    border = false;
};

//-----------------------------------------------------------------------------

singleton GuiControlProfile( VEditorTextProfile : VEditorDefaultProfile )
{
    border = false;
    opaque = false;
    
    fontType = "Arial Bold";
};

singleton GuiControlProfile( VEditorTextEditProfile : VEditorDefaultProfile )
{
    fillColor      = "70 70 70";
    fillColorHL    = "90 90 90";
    fillColorSEL   = "0 0 0";
    fillColorNA    = "70 70 70";
    
    fontColor      = "255 255 255";
    fontColorHL    = "0 0 0";
    fontColorSEL   = "128 128 128";
    fontColorNA    = "128 128 128";
    
    textOffset     = "4 2";
    autoSizeWidth  = false;
    autoSizeHeight = false;
    justify        = "left";
    tab            = true;
    canKeyFocus    = true;
};

singleton GuiControlProfile( VEditorPopupMenuProfile : GuiPopUpMenuProfile )
{
    FillColorHL    = "90 90 90";
    FillColorSEL   = "0 0 0";
    
    FontColorHL    = "255 255 255";
};

singleton GuiControlProfile ( VEditorBitmapButtonProfile : VEditorDefaultProfile  )
{
    justify = "center";
    
    hasBitmapArray = true;
    bitmap         = "./Images/Button";
};

//-----------------------------------------------------------------------------

singleton GuiControlProfile( VEditorGroupHeaderProfile : VEditorDefaultProfile )
{
    CanKeyFocus = true;
    TextOffset  = "23 0";
    
    fontColor   = "70 70 70";
};

singleton GuiControlProfile( VEditorGroupHeaderErrorProfile : VEditorGroupHeaderProfile )
{
    fontColor = "255 70 70";
};

singleton GuiControlProfile( VEditorGroupTrackProfile : VEditorTransparentProfile )
{
    CanKeyFocus = true;
};

singleton GuiControlProfile( VEditorTrackProfile : VEditorDefaultProfile )
{
    CanKeyFocus = true;
    TextOffset  = "33 0";
    
    opaque      = true;
    fillColor   = "255 255 255 15";
    fillColorHL = "151 166 191 60";
    
    borderColor = "100 100 100";
};

singleton GuiControlProfile( VEditorTrackErrorProfile : VEditorTrackProfile )
{
    fontColor = "255 70 70";
};

singleton GuiControlProfile( VEditorEventProfile : VEditorDefaultProfile )
{
    CanKeyFocus   = true;
    Justify       = "left";
    TextOffset    = "6 1";
    
    fillColor     = "81 81 81";
    fillColorHL   = "102 102 102";
    
    borderColor   = "255 255 255";
    borderColorHL = "255 255 255";
    borderColorNA = "100 100 100";
};

singleton GuiControlProfile( VEditorTimeLineProfile : VEditorDefaultProfile )
{
    CanKeyFocus = true;
    
    opaque      = false;
    fillColorHL = "255 255 255 15";
    
    border      = false;
    borderColor = "100 100 100";
};

singleton GuiControlProfile( VEditorPropertyProfile : VEditorDefaultProfile )
{
    fillColor = "102 102 102";
};

//-----------------------------------------------------------------------------

singleton GuiControlProfile ( VEditorScrollProfile : VEditorDefaultProfile )
{
    opaque = false;
    border = false;
    
    hasBitmapArray = true;
    bitmap         = "./Images/ScrollBar";
};

singleton GuiControlProfile ( VEditorCheckBoxProfile : GuiCheckBoxProfile )
{
    // Void.
};

//-----------------------------------------------------------------------------

singleton GuiControlProfile( VEditorPropertyRolloutProfile : GuiRolloutProfile )
{
    border = 0;
    hasBitmapArray = true;
    bitmap = "./Images/PropertyRollout";

    fontType      = "Arial";
    fontSize      = 12;
    fontCharset   = ANSI;

    fontColor     = "255 255 255";
    fontColorHL   = "255 255 255";
    fontColorNA   = "255 255 255";
    fontColorSEL  = "255 255 255";
};

singleton GuiControlProfile( VEditorPropertyLabelProfile : VEditorTextProfile )
{
    border  = "1";
    justify = "center";
};

//-----------------------------------------------------------------------------

singleton GuiControlProfile( VEditorPreferenceLabelProfile : GuiTextProfile )
{
    opaque      = true;
    fillColor   = "242 241 240";
    fillColorHL = "242 241 240";
    fillColorNA = "242 241 240";
};