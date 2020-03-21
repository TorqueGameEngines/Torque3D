new GuiControlProfile (GuiEventBackgroundProfile)
{
   justify = "left";
   fontSize = 18;
   fontColor = "225 225 225 255";

   opaque = true;
   fillColor = "20 20 20 225";
};

new GuiControlProfile (GuiEventBorderProfile)
{
   opaque = false;
   border = 1;
   borderColor   = "225 225 225 255"; 
};

new GuiControlProfile (GuiEventTextProfile)
{
   justify = "left";
   fontSize = 18;
   fontColor = "225 225 225 255";
};

new GuiControlProfile (GuiEventCheckboxProfile : GuiCheckBoxProfile)
{
   fontSize = 18;
   fontColor = "225 225 225 255";
   fontColorHL ="141 204 249 255";
};
