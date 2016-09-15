/* ************************************************************************ 
 *         The Amulet User Interface Development Environment              *
 * ************************************************************************
 * This code has been placed in the public   			          *
 * domain.  If you are using this code or any part of Amulet,             *
 * please contact amulet@cs.cmu.edu to be put on the mailing list.        *
 * ************************************************************************/

/* Originally written as AmEdit by S.Nebel (Linkworks Ltd Wellington,NZ) 1997.
   Modified and updated by Brad A. Myers of the Amulet project at CMU.
*/

#include <amulet.h>
// #include <strstream.h>

#ifdef GCC
#include <string.h>
#else
extern "C" {
#if defined(_MSC_VER) || defined(NEED_STRING)
#include <string.h>
#endif
}
#endif

#include "externs.h"

#define DO_NOT_ADD_PREFIX 2
#define ADD_PREFIX 1
#define ADDPART_PREFIX 0

extern Am_Object graphics_group_proto;
extern Am_Slot_Key REF_COUNT;

char quote[2] = {'"', '\0'};

///////////////////////////////////////////////////

bool
is_in_list(Am_Value_List l, Am_Value item)
{
  l.Start();
  return l.Member(item);
}

void
output_line_styles(bool in_header, ostream &os, Am_Value_List &line_styles)
{
  Am_Value_List l;
  Am_Style s;
  float r, g, b;
  short thickness;
  int dash_l_length;
  Am_Line_Cap_Style_Flag cap;
  Am_Join_Style_Flag join;
  Am_Line_Solid_Flag line_flag;
  const char *dash_l;
  Am_Fill_Solid_Flag fill_flag;
  Am_Fill_Poly_Flag poly;
  Am_Image_Array stipple;
  Am_String name;

  os << "//Line styles exclusivly created by Gilt\n\n";
  for (line_styles.Start(); !line_styles.Last(); line_styles.Next()) {
    l = (Am_Value_List)line_styles.Get();
    l.Start();
    name = (Am_String)l.Get();
    l.Next();
    if (in_header) {
      os << "extern Am_Style " << name << "\n";
    } else {
      s = (Am_Style)l.Get();
      s.Get_Values(r, g, b, thickness, cap, join, line_flag, dash_l,
                   dash_l_length, fill_flag, poly, stipple);
      os << "Am_Style " << name << " = Am_Style::Am_Style(" << r << ", " << g
         << ", " << b << ", " << thickness << ", ";
      os << "Am_CAP_BUTT, Am_JOIN_MITER, ";
      os << "\n                         ";

      switch (line_flag) {
      case Am_LINE_SOLID:
        os << "Am_LINE_SOLID, ";
        break;
      case Am_LINE_ON_OFF_DASH:
        os << "Am_LINE_ON_OFF_DASH, ";
        break;
      }
      switch (dash_l[0]) {
      case 4:
        os << "Am_DEFAULT_DASH_LIST";
        break;
      default:
        os << "{2, 2}";
        break;
      }
      os << ");\n";
    }
  }
  os << "\n\n\n";
}

void
output_images(bool inheader, ostream &os, Am_Value_List &image_list)
{
  Am_Value_List l;
  for (image_list.Start(); !image_list.Last(); image_list.Next()) {
    l = image_list.Get();
    l.Start();
    if (inheader)
      os << "extern Am_Image_Array " << l.Get() << endl;
    else {
      os << "Am_Image_Array " << l.Get();
      l.Next();
      os << "(" << quote << l.Get() << quote << ");" << endl;
    }
  }
  os << "\n\n\n";
}

void
do_prolog(ostream &os, bool in_header_file, bool as_window,
          Am_String wingroup_name, Am_Value_List &slot_names,
          Am_Value_List &line_styles, Am_Value_List &image_list)
{
  os << "/* ************************************************************* *\n";
  os << " *   The Amulet User Interface Development Environment           *\n";
  os << " * ************************************************************* *\n";
  os << " *   Created automatically by the Gilt program in Amulet.        *\n";
  os << " *   Do not edit this file directly.                             *\n";
  os << " *   For more information on Amulet, contact amulet@cs.cmu.edu   *\n";
  os << " * ************************************************************* *\n";
  os << " *   Generated on " << Am_Get_Time_And_Date() << endl;
  os << " *   Amulet version " << Am_VERSION << endl;
  os << " * ************************************************************* */\n";
  if (in_header_file) {
    os << "#ifndef " << wingroup_name << "_H\n";
    os << "#define " << wingroup_name << "_H\n";
  }
  os << "\n#include <amulet.h>\n\n";
  if (in_header_file) {
    os << "extern Am_Object " << wingroup_name << ";\n";
    os << "extern Am_Object " << wingroup_name << "_Initialize ();\n\n";
    output_line_styles(in_header_file, os, line_styles);
    output_images(in_header_file, os, image_list);
  } else {
    os << "Am_Object " << wingroup_name << ";\n\n";
  }
  //output slot names
  Am_String name;
  for (slot_names.Start(); !slot_names.Last(); slot_names.Next()) {
    name = slot_names.Get();
    if (in_header_file)
      os << "extern Am_Slot_Key " << name << ";\n";
    else
      os << "Am_Slot_Key " << name << " = Am_Register_Slot_Name (\"" << name
         << "\");\n";
  }

  //output procedure header
  if (!in_header_file) {

    output_line_styles(in_header_file, os, line_styles);
    output_images(in_header_file, os, image_list);
    os << "\n\nAm_Object " << wingroup_name << "_Initialize () {\n";
    os << "  " << wingroup_name << " = ";
    if (as_window)
      os << "Am_Window";
    else
      os << "Am_Group";
    os << ".Create(\"" << wingroup_name << "\")\n";
  } else {
    os << "\n#endif\n";
  }
}

void
output_wingroup_properties(ostream &os, bool is_window, int fill_key,
                           Am_String title, bool explicit_wh, int width,
                           int height, bool win_fixed_size,
                           Am_String wingroup_name)
{
  if (is_window) {
    os << "    .Set(Am_DESTROY_WINDOW_METHOD, "
          "Am_Default_Pop_Up_Window_Destroy_Method)\n";
    if (fill_key >= 0)
      os << "    .Set(Am_FILL_STYLE, " << n2sstr[fill_key] << ")\n";
    if (title.Valid()) {
      os << "    .Set(Am_TITLE, \"" << title << "\")\n";
      os << "    .Set(Am_ICON_TITLE, \"" << title << "\")\n";
    }
    if (win_fixed_size) {
      //make fixed size window
      os << "    //fixed size window\n";
      os << "    .Set(Am_USE_MIN_WIDTH, true)\n";
      os << "    .Set(Am_USE_MAX_WIDTH, true)\n";
      os << "    .Set(Am_USE_MIN_HEIGHT, true)\n";
      os << "    .Set(Am_USE_MAX_HEIGHT, true)\n";
      os << "    .Set(Am_MIN_WIDTH, Am_Same_As(Am_WIDTH))\n";
      os << "    .Set(Am_MAX_WIDTH, Am_Same_As(Am_WIDTH))\n";
      os << "    .Set(Am_MIN_HEIGHT, Am_Same_As(Am_HEIGHT))\n";
      os << "    .Set(Am_MAX_HEIGHT, Am_Same_As(Am_HEIGHT))\n";
    }
  } //end is_window
  if (explicit_wh) {
    os << "    .Set(Am_WIDTH, " << width << ")\n";
    os << "    .Set(Am_HEIGHT, " << height << ")\n";
  } else {
    os << "    .Set(Am_WIDTH , Am_Width_Of_Parts)\n";
    os << "    .Set(Am_HEIGHT, Am_Height_Of_Parts)\n";
  }
  os << "    ;\n";
  os << "  " << wingroup_name << "\n";
}

void
output_tab_interactor(ostream &os)
{
  os << "    .Add_Part(Am_Tab_To_Next_Widget_Interactor.Create())\n";
}

void
do_epilog(ostream &os, Am_String wingroup_name)
{
  os << "  ;\n";
  os << "  return " << wingroup_name << ";\n";
  os << "}\n";
}

void
stringout(ostream &os, const char *s)
{
  if (strchr(s, '\"')) {
    char *news = new char[strlen(s) * 2];
    int j = 0;
    for (int i = 0; s[i] != 0; i++) {
      if (s[i] == '\"' || s[i] == '\\')
        news[j++] = '\\'; //preceed with a backslash
      news[j++] = s[i];
    }
    news[j] = 0;
    os << "\"" << news << "\"";
    delete news;
  } else
    os << "\"" << s << "\"";
}

//forward declaration
static void output_group(ostream &os, char *indent, Am_Object &obj, int mode);
void output_object(ostream &os, char *indent, Am_Object &obj, int do_add);

void
slotout(ostream &os, char *indent, const Am_Object &obj, const char *slot_name,
        Am_Slot_Key key)
{
  os << indent << "  .Set(" << slot_name;
  Am_Value value = obj.Get(key);
  if (value.type == Am_NONE)
    os << ", Am_No_Value)\n";
  else if (value.type == Am_STRING) {

    os << ", ";
    Am_String s = value;
    stringout(os, s);
    os << ")\n";
  } else
    os << ", " << value << ")\n";
}

void
layoutout(ostream &os, char *indent, const Am_Object &obj)
{
  os << indent << "  .Set(Am_LAYOUT, " << layout[(int)obj.Get(LAYOUT_KEY)]
     << ")\n";
}
void
linestyleout(ostream &os, char *indent, const Am_Object &obj)
{
  int i, j;
  Am_Value_List key = obj.Get(LINE_STYLE_KEY);
  key.Start();
  i = (int)key.Get();
  key.Next();
  j = (int)key.Get();
  os << indent << "  .Set(Am_LINE_STYLE, " << n2lstr[i][j] << ")\n";
}
void
fillstyleout(ostream &os, char *indent, const Am_Object &obj)
{
  os << indent << "  .Set(Am_FILL_STYLE, "
     << n2sstr[(int)obj.Get(FILL_STYLE_KEY)] << ")\n";
}

void
itemsout(ostream &os, char *indent, Am_Object &obj)
{
  os << indent << "  .Set(Am_ITEMS, Am_Value_List()\n";
  Am_Value_List l = obj.Get(Am_ITEMS);
  int cnt = 1;
  Am_String name;
  Am_Value v = obj.Peek(SAVE_MENU_BAR);

  if (v.Valid() && (bool)v) {
    Am_Object cmd;
    char newindent[100];
    sprintf(newindent, "%s     ", indent);
    for (l.Start(); !l.Last(); l.Next()) {
      cmd = (Am_Object)l.Get();
      output_object(os, newindent, cmd, ADD_PREFIX);
    }
  } else {
    for (l.Start(); !l.Last(); l.Next()) {
      name = l.Get();
      os << indent << "    .Add(Am_Command.Create()\n";
      os << indent << "         .Set(Am_LABEL, ";
      stringout(os, name);
      os << ")\n";
      os << indent << "         .Set(Am_ID, " << cnt++ << "))\n";
    }
  }
  os << indent << "    )\n";
}

void
pointlistout(ostream &os, char *indent, Am_Object &obj)
{
  os << indent << "  .Set(Am_POINT_LIST, Am_Point_List()\n";
  Am_Point_List l = obj.Get(Am_POINT_LIST);
  float x, y;
  for (l.Start(); !l.Last(); l.Next()) {
    l.Get(x, y);
    os << indent << "    .Add(" << x << ", " << y << ")\n";
  }
  os << indent << "    )\n";
}
void
sublabelout(ostream &os, char *indent, Am_Object &obj)
{
  Am_Value v = obj.Get_Object(Am_COMMAND).Get(Am_LABEL);
  char s[100];

  os << indent << "  .Get_Object(Am_COMMAND)\n";
  os << indent << "    .Set(Am_LABEL, ";

  if (v.type == Am_STRING) {
    stringout(os, (char *)(Am_String)v);
  } else if (v.type == Am_OBJECT) {
    sprintf(s, "         %s", indent);
    Am_Object label_obj = (Am_Object)v;
    if (((Am_Value)label_obj.Peek(Am_GRAPHICAL_PARTS)).Valid()) {
      output_group(os, s, label_obj, DO_NOT_ADD_PREFIX);
    } else
      output_object(os, s, label_obj, DO_NOT_ADD_PREFIX);
  }
  sprintf(s, "      %s", indent);
  os << s << ")\n";
  os << indent << "    .Get_Owner()\n";
}

void
itemcmdsout(ostream &os, char *indent, Am_Object &obj)
{
  os << indent << "  .Set(Am_ITEMS, Am_Value_List()\n";
  Am_Value_List l = obj.Get(Am_ITEMS);
  Am_Object cmd;
  for (l.Start(); !l.Last(); l.Next()) {
    cmd = l.Get();
    os << indent << "    .Add(" << cmd.Get_Prototype().Get_Name()
       << ".Create())\n";
  }
  os << indent << "    )\n";
}

char *
convert_to_ia(char *fname)
{
  char *ptr;
  ptr = fname;
  while (*ptr != '\0') {
    if (*ptr == '.' || *ptr == '/')
      *ptr = '_';
    ptr++;
  }

  return fname;
}

void
fileimageout(ostream &os, char *indent, Am_Object &obj)
{
  Am_String filename = obj.Get(FILE_NAME);

  os << indent << "  .Set(Am_IMAGE, " << convert_to_ia((char *)filename) << ")"
     << endl;
}

void
fontout(ostream &os, char *indent, Am_Object &obj)
{
  Am_Value_List fk = obj.Get(FONT_KEY);
  int type, size, style;
  fk.Start();
  type = fk.Get();
  fk.Next();
  size = fk.Get();
  fk.Next();
  style = fk.Get();

  Am_Font font = fontarray[type][size][style];
  Am_String name;
  Am_Font_Family_Flag f;
  bool is_bold;
  bool is_italic;
  bool is_underline;
  Am_Font_Size_Flag s;
  font.Get(name, f, is_bold, is_italic, is_underline, s);
  //first, check if default font
  if (name.Valid() || f != Am_FONT_FIXED || is_bold || is_italic ||
      is_underline || s != Am_FONT_MEDIUM) { //different from default
    os << indent << "  .Set(Am_FONT, Am_Font(";
    if (name.Valid())
      os << name;
    else {
      switch (f) {
      case Am_FONT_FIXED:
        os << "Am_FONT_FIXED, ";
        break;
      case Am_FONT_SERIF:
        os << "Am_FONT_SERIF, ";
        break;
      case Am_FONT_SANS_SERIF:
        os << "Am_FONT_SANS_SERIF, ";
        break;
      case Am_FONT_JFIXED:
        os << "Am_FONT_JFIXED, ";
        break;
      case Am_FONT_JPROPORTIONAL:
        os << "Am_FONT_JPROPORTIONAL, ";
        break;
      case Am_FONT_CFIXED:
        os << "Am_FONT_CFIXED, ";
        break;
      case Am_FONT_KFIXED:
        os << "Am_FONT_KFIXED, ";
        break;
      }
      if (is_bold)
        os << "true, ";
      else
        os << "false, ";
      if (is_italic)
        os << "true, ";
      else
        os << "false, ";
      if (is_underline)
        os << "true, ";
      else
        os << "false, ";
      switch (s) {
      case Am_FONT_SMALL:
        os << "Am_FONT_SMALL";
        break;
      case Am_FONT_MEDIUM:
        os << "Am_FONT_MEDIUM";
        break;
      case Am_FONT_LARGE:
        os << "Am_FONT_LARGE";
        break;
      case Am_FONT_VERY_LARGE:
        os << "Am_FONT_VERY_LARGE";
        break;
      case Am_FONT_TSMALL:
        os << "Am_FONT_TSMALL";
        break;
      case Am_FONT_TMEDIUM:
        os << "Am_FONT_TMEDIUM";
        break;
      case Am_FONT_TLARGE:
        os << "Am_FONT_TLARGE";
        break;
      case Am_FONT_TVERY_LARGE:
        os << "Am_FONT_TVERY_LARGE";
        break;
      }
    }
    os << "))\n";
  }
}

void
output_add_part(ostream &os, char *indent, Am_Object &obj, int is_list)
{
  Am_String name = obj.Get(Lw_NAME, Am_RETURN_ZERO_ON_ERROR);
  if (is_list == 1)
    os << indent << ".Add(";
  else if (is_list == 0)
    os << indent << ".Add_Part(";

  if (name.Valid() && !(name == "")) {
    os << name << ", ";
  }
  Am_String type_name = obj.Get(TYPE_NAME);
  os << type_name << ".Create(";
  if (name.Valid() && !(name == ""))
    stringout(os, name);
  os << ")\n";
}

void
output_object(ostream &os, char *indent, Am_Object &obj, int is_add)
{
  output_add_part(os, indent, obj, is_add);
  Am_Value_List slots = obj.Get(Am_SLOTS_TO_SAVE);

  Am_Slot_Key slot;
  for (slots.Start(); !slots.Last(); slots.Next()) {
    slot = (int)slots.Get();
    switch (slot) {
    case Am_LEFT:
      slotout(os, indent, obj, "Am_LEFT", Am_LEFT);
      break;
    case Am_TOP:
      slotout(os, indent, obj, "Am_TOP", Am_TOP);
      break;
    case Am_WIDTH:
      slotout(os, indent, obj, "Am_WIDTH", Am_WIDTH);
      break;
    case Am_HEIGHT:
      slotout(os, indent, obj, "Am_HEIGHT", Am_HEIGHT);
      break;
    case Am_X1:
      slotout(os, indent, obj, "Am_X1", Am_X1);
      break;
    case Am_Y1:
      slotout(os, indent, obj, "Am_Y1", Am_Y1);
      break;
    case Am_X2:
      slotout(os, indent, obj, "Am_X2", Am_X2);
      break;
    case Am_Y2:
      slotout(os, indent, obj, "Am_Y2", Am_Y2);
      break;
    case Am_TEXT:
      slotout(os, indent, obj, "Am_TEXT", Am_TEXT);
      break;
    case Am_SELECTED:
      slotout(os, indent, obj, "Am_SELECTED", Am_SELECTED);
      break;
    case Am_VALUE_1:
      slotout(os, indent, obj, "Am_VALUE_1", Am_VALUE_1);
      break;
    case Am_VALUE_2:
      slotout(os, indent, obj, "Am_VALUE_2", Am_VALUE_2);
      break;
    case Am_INNER_WIDTH:
      slotout(os, indent, obj, "Am_INNER_WIDTH", Am_INNER_WIDTH);
      break;
    case Am_INNER_HEIGHT:
      slotout(os, indent, obj, "Am_INNER_HEIGHT", Am_INNER_HEIGHT);
      break;
    case Am_H_SCROLL_BAR:
      slotout(os, indent, obj, "Am_H_SCROLL_BAR", Am_H_SCROLL_BAR);
      break;
    case Am_V_SCROLL_BAR:
      slotout(os, indent, obj, "Am_V_SCROLL_BAR", Am_V_SCROLL_BAR);
      break;
    case Am_H_SCROLL_BAR_ON_TOP:
      slotout(os, indent, obj, "Am_H_SCROLL_BAR_ON_TOP",
              Am_H_SCROLL_BAR_ON_TOP);
      break;
    case Am_V_SCROLL_BAR_ON_LEFT:
      slotout(os, indent, obj, "Am_V_SCROLL_BAR_ON_LEFT",
              Am_V_SCROLL_BAR_ON_LEFT);
      break;
    case Am_H_SPACING:
      slotout(os, indent, obj, "Am_H_SPACING", Am_H_SPACING);
      break;
    case Am_V_SPACING:
      slotout(os, indent, obj, "Am_V_SPACING", Am_V_SPACING);
      break;
    case Am_MAX_RANK:
      slotout(os, indent, obj, "Am_MAX_RANK", Am_MAX_RANK);
      break;

    case Am_POINT_LIST:
      pointlistout(os, indent, obj);
      break;
    case Am_ITEMS:
      itemsout(os, indent, obj);
      break;
    case Am_ACCELERATOR:
      slotout(os, indent, obj, "Am_ACCELERATOR", Am_ACCELERATOR);
      break;
    case Am_LABEL:
      slotout(os, indent, obj, "Am_LABEL", Am_LABEL);
      break;
    default: { //can't do the allocated slots with switch since not constants
      if (slot == LAYOUT_KEY)
        layoutout(os, indent, obj);
      else if (slot == SUB_LABEL)
        sublabelout(os, indent, obj);
      else if (slot == FONT_KEY)
        fontout(os, indent, obj);
      else if (slot == LINE_STYLE_KEY)
        linestyleout(os, indent, obj);
      else if (slot == FILL_STYLE_KEY)
        fillstyleout(os, indent, obj);
      else if (slot == SAVE_COMMAND_ITEMS)
        itemcmdsout(os, indent, obj);
      else if (slot == Lw_NAME)
        ; //already handled
      else if (slot == COMMAND_KEY)
        ;
      else if (slot == FILE_NAME)
        fileimageout(os, indent, obj);
      else if (slot == Am_IMAGE)
        ;
      else if (slot == Am_ACTIVE_2)
        ;
      else if (slot == Am_ACTIVE)
        ;
      else if (slot == CONSTRAINT_INFO)
        ;
      else if (slot == REF_COUNT)
        ;
      else
        Am_ERROR("Don't know how to save slot "
                 << Am_Value(slot, Am_SLOT_KEY_TYPE));
    } // default
    } //switch
  }   //loop
  if (is_add != DO_NOT_ADD_PREFIX)
    os << indent << ")\n";
}

void
output_all_parts(ostream &os, char *indent, Am_Value_List &parts)
{
  Am_Object part;
  for (parts.Start(); !parts.Last(); parts.Next()) {
    Am_Object part = parts.Get();
    if (part.Is_Instance_Of(Am_Resize_Parts_Group) ||
        part.Is_Instance_Of(graphics_group_proto))
      output_group(os, indent, part, ADDPART_PREFIX);
    else {
      output_object(os, indent, part, ADDPART_PREFIX);
    }
  }
}

static void
output_group(ostream &os, char *indent, Am_Object &obj, int mode)
{
  output_add_part(os, indent, obj, mode);
  slotout(os, indent, obj, "Am_LEFT", Am_LEFT);
  slotout(os, indent, obj, "Am_TOP", Am_TOP);
  slotout(os, indent, obj, "Am_WIDTH", Am_WIDTH);
  slotout(os, indent, obj, "Am_HEIGHT", Am_HEIGHT);
  char newindent[100];
  sprintf(newindent, "%s  ", indent); //add two more spaces
  Am_Value_List l = obj.Get(Am_GRAPHICAL_PARTS);
  output_all_parts(os, newindent, l);
  if (mode != DO_NOT_ADD_PREFIX)
    os << indent << ")\n";
}

void
Generate_Slot_Names(Am_Value_List &objs_list, Am_Value_List &slot_names,
                    bool &has_text_input_part)
{
  Am_Object obj;
  Am_String name;
  has_text_input_part = false;
  for (objs_list.Start(); !objs_list.Last(); objs_list.Next()) {
    obj = objs_list.Get();
    if (obj.Is_Instance_Of(Am_Text_Input_Widget))
      has_text_input_part = true;
    name = obj.Get(Lw_NAME, Am_RETURN_ZERO_ON_ERROR);
    if (name.Valid() && !(name == ""))
      slot_names.Add(name);
    if (obj.Is_Instance_Of(Am_Resize_Parts_Group)) {
      Am_Value_List sub_parts = obj.Get(Am_GRAPHICAL_PARTS);
      Generate_Slot_Names(sub_parts, slot_names, has_text_input_part);
    }
  }
}

void
Generate_Line_Styles_Image_Array(Am_Value_List &obj_list,
                                 Am_Value_List &style_list,
                                 Am_Value_List &image_list)
{

  Am_Object obj;
  Am_String name;
  int i, j;
  Am_Value v;
  Am_Value_List key;
  Am_Style s;

  for (obj_list.Start(); !obj_list.Last(); obj_list.Next()) {
    obj = obj_list.Get();

    v = obj.Peek(Am_GRAPHICAL_PARTS);
    if (v.Exists()) {
      Am_Value_List pl = (Am_Value_List)v;
      Generate_Line_Styles_Image_Array(pl, style_list, image_list);
    }

    v = obj.Peek(SUB_LABEL);
    if (v.Exists()) {
      if (!Am_String::Test(v))
        Generate_Line_Styles_Image_Array(Am_Value_List().Add(v), style_list,
                                         image_list);
    }

    v = obj.Peek(LINE_STYLE_KEY);
    if (v.Valid()) {
      key = (Am_Value_List)v;
      key.Start();
      i = (int)key.Get();
      key.Next();
      j = (int)key.Get();
      name = n2lstr[i][j];
      if (i !=
          8) { //if i == 8, I can just use Am_Line_x instead of define new one
        s = n2l[i][j];
        key = Am_Value_List().Add(name).Add(s);
        if (!is_in_list(style_list, (Am_Value)key))
          style_list.Add(key);
      }
    }

    if (obj.Is_Instance_Of(button_proto)) {
      v = obj.Get_Object(Am_COMMAND).Get(Am_LABEL);
      if (v.type == Am_OBJECT)
        obj = (Am_Object)v;
    }
    v = obj.Peek(FILE_NAME);
    if (v.Valid()) {
      key = Am_Value_List()
                .Add(convert_to_ia((char *)(Am_String)v))
                .Add((Am_String)v);
      if (!is_in_list(image_list, (Am_Value)key))
        image_list.Add(key);
    }
  }
}

///////////////////////////////////////////////////////////////////////////
// Main exported routines
///////////////////////////////////////////////////////////////////////////

void
output_cc_with_header(ostream &os_h, ostream &os_cc, bool is_window,
                      Am_Value_List &top_level_objs_list,
                      Am_String wingroup_name, int fill_key, Am_String title,
                      bool explicit_wh, int width, int height,
                      bool win_fixed_size)
{
  Am_Value_List slot_names, line_style_list, image_list;
  bool has_text_input_part;
  Generate_Slot_Names(top_level_objs_list, slot_names, has_text_input_part);
  Generate_Line_Styles_Image_Array(top_level_objs_list, line_style_list,
                                   image_list);
  cout << "Line_style are " << line_style_list << endl;
  cout << "Image_List are " << image_list << endl;
  do_prolog(os_h, true, true, wingroup_name, slot_names, line_style_list,
            image_list);

  do_prolog(os_cc, false, is_window, wingroup_name, slot_names, line_style_list,
            image_list);
  output_wingroup_properties(os_cc, is_window, fill_key, title, explicit_wh,
                             width, height, win_fixed_size, wingroup_name);
  output_all_parts(os_cc, "    ", top_level_objs_list);
  if (has_text_input_part)
    output_tab_interactor(os_cc);
  do_epilog(os_cc, wingroup_name);
}

void
output_cc_no_header(ostream &os_cc, bool is_window,
                    Am_Value_List &top_level_objs_list, Am_String wingroup_name,
                    int fill_key, Am_String title, bool explicit_wh, int width,
                    int height, bool win_fixed_size)
{
  bool has_text_input_part;
  Am_Value_List slot_names, line_style_list, image_list;
  Generate_Slot_Names(top_level_objs_list, slot_names, has_text_input_part);
  Generate_Line_Styles_Image_Array(top_level_objs_list, line_style_list,
                                   image_list);
  do_prolog(os_cc, false, is_window, wingroup_name, slot_names, line_style_list,
            image_list);
  output_wingroup_properties(os_cc, is_window, fill_key, title, explicit_wh,
                             width, height, win_fixed_size, wingroup_name);
  output_all_parts(os_cc, "    ", top_level_objs_list);
  if (has_text_input_part)
    output_tab_interactor(os_cc);
  do_epilog(os_cc, wingroup_name);
}
