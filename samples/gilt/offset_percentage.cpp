/* ************************************************************* *
 *   The Amulet User Interface Development Environment           *
 * ************************************************************* *
 *   Created automatically by the Gilt program in Amulet.        *
 *   Do not edit this file directly.                             *
 *   For more information on Amulet, contact amulet@cs.cmu.edu   *
 * ************************************************************* *
 *   Generated on Sun Aug 03 02:04:11 1997

 *   Amulet version 4.0 Development
 * ************************************************************* */

#include <amulet.h>

Am_Object Offset_Percentage_Dialog;

//Line styles exclusivly created by Gilt
//test commant








Am_Object Offset_Percentage_Dialog_Initialize () {
  Offset_Percentage_Dialog = Am_Window.Create("Offset_Percentage_Dialog")
    .Set(Am_DESTROY_WINDOW_METHOD, Am_Default_Pop_Up_Window_Destroy_Method)
    .Set(Am_FILL_STYLE, Am_Motif_Gray)
    .Set(Am_TITLE, "COnstraint Setup")
    .Set(Am_ICON_TITLE, "COnstraint Setup")
    .Set(Am_WIDTH , Am_Width_Of_Parts)
    .Set(Am_HEIGHT, Am_Height_Of_Parts)
    ;
  Offset_Percentage_Dialog
    .Add_Part(Am_Border_Rectangle.Create()
      .Set(Am_LEFT, 17)
      .Set(Am_TOP, 13)
      .Set(Am_WIDTH, 168)
      .Set(Am_HEIGHT, 94)
      .Set(Am_SELECTED, 0)
      .Set(Am_FILL_STYLE, Am_Motif_Gray)
    )
    .Add_Part(Am_Number_Input_Widget.Create()
      .Set(Am_LEFT, 33)
      .Set(Am_TOP, 68)
      .Set(Am_WIDTH, 137)
      .Set(Am_HEIGHT, 25)
      .Set(Am_FILL_STYLE, Am_Amulet_Purple)
      .Get_Object(Am_COMMAND)
        .Set(Am_LABEL, "Offset : "          )
        .Get_Owner()
      .Set(Am_VALUE_1, Am_No_Value)
      .Set(Am_VALUE_2, Am_No_Value)
    )
    .Add_Part(Am_Number_Input_Widget.Create()
      .Set(Am_LEFT, 33)
      .Set(Am_TOP, 32)
      .Set(Am_WIDTH, 136)
      .Set(Am_HEIGHT, 25)
      .Set(Am_FILL_STYLE, Am_Amulet_Purple)
      .Get_Object(Am_COMMAND)
        .Set(Am_LABEL, "Percentage : "          )
        .Get_Owner()
      .Set(Am_VALUE_1, Am_No_Value)
      .Set(Am_VALUE_2, Am_No_Value)
    )
    .Add_Part(Am_Button_Panel.Create()
      .Set(Am_LEFT, 14)
      .Set(Am_TOP, 117)
      .Set(Am_FILL_STYLE, Am_Motif_Gray)
      .Set(Am_ITEMS, Am_Value_List()
        .Add(Am_Command.Create()
             .Set(Am_LABEL, "Custom")
             .Set(Am_ID, 1))
        .Add(Am_Command.Create()
             .Set(Am_LABEL, "Apply")
             .Set(Am_ID, 2))
        .Add(Am_Command.Create()
             .Set(Am_LABEL, "Cancel")
             .Set(Am_ID, 3))
        )
      .Set(Am_LAYOUT, Am_Horizontal_Layout)
      .Set(Am_H_SPACING, 5)
      .Set(Am_V_SPACING, 0)
      .Set(Am_MAX_RANK, 0)
    )
    .Add_Part(Am_Tab_To_Next_Widget_Interactor.Create())
  ;
  return Offset_Percentage_Dialog;
}
