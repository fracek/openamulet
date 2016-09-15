/* ************************************************************* *
 *   The Amulet User Interface Development Environment           *
 * ************************************************************* *
 *   Created automatically by the Gilt program in Amulet.        *
 *   Do not edit this file directly.                             *
 *   For more information on Amulet, contact amulet@cs.cmu.edu   *
 * ************************************************************* *
 *   Generated on Tue Jan 21 21:20:36 1997

 *   Amulet version 3.0 alpha
 * ************************************************************* */

#include <amulet.h>
#include "externs.h"

Am_Object Border_Rect_Window;

Am_Slot_Key LOOKS_SELECTED_OBJ = Am_Register_Slot_Name("LOOKS_SELECTED_OBJ");

Am_Object
Border_Rect_Window_Initialize()
{
  Border_Rect_Window =
      Am_Window.Create("MainWindow")
          .Set(Am_DESTROY_WINDOW_METHOD,
               Am_Default_Pop_Up_Window_Destroy_Method)
          .Set(Am_FILL_STYLE, Am_Motif_Light_Gray)
          .Set(Am_TITLE, "Some Application")
          .Set(Am_ICON_TITLE, "Some Application")
          .Set(Am_WIDTH, 336)
          .Set(Am_HEIGHT, 122)
          .Add_Part(Am_Border_Rectangle.Create()
                        .Set(Am_LEFT, 0)
                        .Set(Am_TOP, 0)
                        .Set(Am_WIDTH, 336)
                        .Set(Am_HEIGHT, 122)
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
                  .Set(Am_LEFT, 90)
                  .Set(Am_TOP, 73)
                  .Set(Am_FILL_STYLE, Am_Motif_Light_Gray)
                  .Set(Am_LAYOUT, Am_Horizontal_Layout)
                  .Set(Am_H_SPACING, 40)
                  .Set(Am_V_SPACING, 0)
                  .Set(Am_MAX_RANK, 0)
                  .Set(Am_ITEMS, Am_Value_List()
                                     .Add(Am_Standard_OK_Command.Create())
                                     .Add(Am_Standard_Cancel_Command.Create())))
          .Add_Part(LOOKS_SELECTED_OBJ,
                    Am_Checkbox_Panel.Create("LOOKS_SELECTED_OBJ")
                        .Set(Am_LEFT, 19)
                        .Set(Am_TOP, 42)
                        .Set(Am_FILL_STYLE, Am_Motif_Light_Gray)
                        .Set(Am_ITEMS, Am_Value_List().Add(
                                           Am_Command.Create()
                                               .Set(Am_LABEL, "Looks Selected")
                                               .Set(Am_ID, 1)))
                        .Set(Am_LAYOUT, Am_Vertical_Layout)
                        .Set(Am_H_SPACING, 0)
                        .Set(Am_V_SPACING, 0)
                        .Set(Am_MAX_RANK, 0))
          .Add_Part(Am_Tab_To_Next_Widget_Interactor.Create());
  return Border_Rect_Window;
}
