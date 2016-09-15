/* ************************************************************* *
 *   The Amulet User Interface Development Environment           *
 * ************************************************************* *
 *   Created automatically by the Gilt program in Amulet.        *
 *   Do not edit this file directly.                             *
 *   For more information on Amulet, contact amulet@cs.cmu.edu   *
 * ************************************************************* *
 *   Generated on Tue Jan 21 17:37:31 1997

 *   Amulet version 3.0 alpha
 * ************************************************************* */

#include <amulet.h>
#include "externs.h"

Am_Object Number_Input_Window;

Am_Slot_Key MIN_VALUE = Am_Register_Slot_Name("MIN_VALUE");
Am_Slot_Key RESTRICTED = Am_Register_Slot_Name("RESTRICTED");
Am_Slot_Key MAX_VALUE = Am_Register_Slot_Name("MAX_VALUE");
Am_Slot_Key LABEL_OBJ = Am_Register_Slot_Name("LABEL_OBJ");

Am_Define_Formula(bool, active_if_restricted)
{
  Am_Value_List v = self.Get_Sibling(RESTRICTED).Get(Am_VALUE);
  v.Start();
  if (v.Member(1))
    return true;
  return false;
}

Am_Object
Number_Input_Window_Initialize()
{
  Number_Input_Window =
      Am_Window.Create("Number_Input_Window")
          .Set(Am_DESTROY_WINDOW_METHOD,
               Am_Default_Pop_Up_Window_Destroy_Method)
          .Set(Am_FILL_STYLE, Am_White)
          .Set(Am_TITLE, "Number Input Settings")
          .Set(Am_ICON_TITLE, "Settings: Number Input")
          .Set(Am_WIDTH, 389)
          .Set(Am_HEIGHT, 247)
          .Add_Part(Am_Border_Rectangle.Create()
                        .Set(Am_LEFT, 0)
                        .Set(Am_TOP, 0)
                        .Set(Am_WIDTH, 389)
                        .Set(Am_HEIGHT, 247)
                        .Set(Am_SELECTED, 0)
                        .Set(Am_FILL_STYLE, Am_Motif_Light_Gray))
          .Add_Part(Am_Border_Rectangle.Create()
                        .Set(Am_LEFT, 55)
                        .Set(Am_TOP, 72)
                        .Set(Am_WIDTH, 260)
                        .Set(Am_HEIGHT, 103)
                        .Set(Am_SELECTED, 0)
                        .Set(Am_FILL_STYLE, Am_Motif_Light_Gray))
          .Add_Part(NAME_OBJ, Am_Text_Input_Widget.Create("NAME_OBJ")
                                  .Set(Am_LEFT, 14)
                                  .Set(Am_TOP, 13)
                                  .Set(Am_WIDTH, 319)
                                  .Set(Am_HEIGHT, 24)
                                  .Get_Object(Am_COMMAND)
                                  .Set(Am_LABEL, "Name for item:")
                                  .Get_Owner()
                                  .Set(Am_FILL_STYLE, Am_Motif_Light_Gray))
          .Add_Part(
              Am_Button_Panel.Create()
                  .Set(Am_LEFT, 113)
                  .Set(Am_TOP, 188)
                  .Set(Am_FILL_STYLE, Am_Motif_Light_Gray)
                  .Set(Am_LAYOUT, Am_Horizontal_Layout)
                  .Set(Am_H_SPACING, 40)
                  .Set(Am_V_SPACING, 0)
                  .Set(Am_MAX_RANK, 0)
                  .Set(Am_ITEMS, Am_Value_List()
                                     .Add(Am_Standard_OK_Command.Create())
                                     .Add(Am_Standard_Cancel_Command.Create())))
          .Add_Part(LABEL_OBJ, Am_Text_Input_Widget.Create("LABEL_OBJ")
                                   .Set(Am_LEFT, 70)
                                   .Set(Am_TOP, 40)
                                   .Set(Am_WIDTH, 263)
                                   .Set(Am_HEIGHT, 25)
                                   .Get_Object(Am_COMMAND)
                                   .Set(Am_LABEL, "Label:")
                                   .Get_Owner()
                                   .Set(Am_FILL_STYLE, Am_Motif_Light_Gray))
          .Add_Part(MIN_VALUE, Am_Number_Input_Widget.Create("MIN_VALUE")
                                   .Set(Am_LEFT, 133)
                                   .Set(Am_TOP, 104)
                                   .Set(Am_WIDTH, 154)
                                   .Set(Am_HEIGHT, 25)
                                   .Set(Am_FILL_STYLE, Am_Motif_Light_Gray)
                                   .Set(Am_ACTIVE, active_if_restricted)
                                   .Get_Object(Am_COMMAND)
                                   .Set(Am_LABEL, "Minimum Value")
                                   .Get_Owner()
                                   .Set(Am_VALUE_1, Am_No_Value)
                                   .Set(Am_VALUE_2, Am_No_Value))
          .Add_Part(
              RESTRICTED,
              Am_Checkbox_Panel.Create("RESTRICTED")
                  .Set(Am_LEFT, 78)
                  .Set(Am_TOP, 84)
                  .Set(Am_FONT, Am_Font(Am_FONT_FIXED, true, false, false,
                                        Am_FONT_MEDIUM))
                  .Set(Am_FILL_STYLE, Am_Motif_Light_Gray)
                  .Set(Am_ITEMS,
                       Am_Value_List().Add(
                           Am_Command.Create()
                               .Set(Am_LABEL, "Restrict Values to a Range")
                               .Set(Am_ID, 1)))
                  .Set(Am_LAYOUT, Am_Vertical_Layout)
                  .Set(Am_H_SPACING, -3)
                  .Set(Am_V_SPACING, -3)
                  .Set(Am_MAX_RANK, 0))
          .Add_Part(MAX_VALUE, Am_Number_Input_Widget.Create("MAX_VALUE")
                                   .Set(Am_LEFT, 133)
                                   .Set(Am_TOP, 132)
                                   .Set(Am_WIDTH, 154)
                                   .Set(Am_HEIGHT, 25)
                                   .Set(Am_FILL_STYLE, Am_Motif_Light_Gray)
                                   .Set(Am_ACTIVE, active_if_restricted)
                                   .Get_Object(Am_COMMAND)
                                   .Set(Am_LABEL, "Maximum Value")
                                   .Get_Owner()
                                   .Set(Am_VALUE_1, Am_No_Value)
                                   .Set(Am_VALUE_2, Am_No_Value))
          .Add_Part(Am_Tab_To_Next_Widget_Interactor.Create());
  return Number_Input_Window;
}
