// generated by Fast Light User Interface Designer (fluid) version 1.0109

#include "appsaudit.h"
// (c) Robert Shingledecker 2009
#include <iostream>
#include <fstream>
#include <string>
#include <FL/fl_message.H>
#include <FL/Fl_File_Chooser.H>
using namespace std;
static string tcedir; 
static string last_dir; 
static string select_extn, select_results; 
static string option_type, report_type; 
static ifstream ifaberr; 
static string aberr; 
static string msg; 
static string copy2fsList, copy2fsFlag; 

void options_callback(Fl_Widget *, void* userdata) {
  option_type = (const char*) userdata;
string command;
report_type = "";

if (userdata == "default")
{
   command = "ls "+ copy2fsFlag + " >/dev/null 2>&1";
   int results = system(command.c_str());
   if (results == 0)
   {
     command = "rm -f "+ copy2fsFlag;
     system(command.c_str());
     box_results->label("copy2fs.flg removed.");
   } else
   {  
     command = "touch " + tcedir + "/copy2fs.flg";
     system(command.c_str());
     box_results->label("copy2fs.flg set");
   }
} else if (userdata == "select") 
{
   box_extensions->label(tcedir.c_str());
   command = "ls " + tcedir + "|grep -E .tcz[ml]*$ > /tmp/tce.lst";
   system(command.c_str());
   brw_extn->load("/tmp/tce.lst");
   brw_results->load(copy2fsList.c_str());
   box_results->label("Current copy2fs.lst");
} else if (userdata == "quit")
{
    exit(0);
}
}

void depends_callback(Fl_Widget *, void* userdata) {
  report_type = (const char*) userdata;
option_type = "";

if (userdata == "builddb")
{
   system("/usr/bin/tce-audit builddb");
   brw_extn->load("/tmp/tce.lst");
   brw_results->load("/tmp/audit_results.txt");
   menu_nodepends->activate();
   menu_auditall->activate();
   menu_marked->activate();
} else if (userdata == "dependson" or userdata == "requiredby" or userdata == "audit") 
{
   report_type = (const char*) userdata;
   string loadit = "tce-audit " + report_type + " " + select_extn;
   int results = system(loadit.c_str());
   if (results == 0 )
   {
      brw_results->load("/tmp/audit_results.txt");
   } else {
      fl_message("error detected!");
   }
} else if (userdata == "auditall" or userdata == "nodepends")
{
   box_results->label("Results");
   menu_delete->deactivate();
   menu_dependson->deactivate();
   menu_requiredby->deactivate();
   menu_missing->deactivate();
   string grabit = "tce-audit " + report_type;
// cout << grabit << endl;
   int results = system(grabit.c_str());
   if (results == 0 )
   {
      brw_results->load("/tmp/audit_results.txt");
   } else {
      ifstream ifaberr("/tmp/aberr");
      msg = "Error: ";
      getline(ifaberr,aberr);
      while (ifaberr) 
      {
         msg = msg + aberr + "\n";
         getline(ifaberr,aberr);
      }
      ifaberr.close();
      fl_message(msg.c_str());
   }
} else if (userdata == "delete")
{
   report_type = (const char*) userdata;
   string loadit = "tce-audit " + report_type + " " + select_extn;
   int results = system(loadit.c_str());
   if (results == 0 )
   {
      brw_results->load("/tmp/audit_results.txt");
   } else {
      fl_message("error detected!");
   }
} else if (userdata == "display_marked")
{
     box_results->label("Results");
     brw_results->load("/tmp/audit_marked.lst");
} else if (userdata == "quit")
{
    exit(0);
}
}

void brw_extn_callback(Fl_Widget *, void *) {
  if (brw_extn->value())
{
   select_extn = brw_extn->text(brw_extn->value());
   if ( report_type.length() > 0 )
   {
     box_results->label(select_extn.c_str());
     menu_dependson->activate();
     menu_requiredby->activate();
     menu_missing->activate();
     menu_delete->activate();
     brw_results->load("");
   } else
   {
     string command = "echo " + select_extn + " >> " + copy2fsList;
     system(command.c_str());
     brw_results->load(copy2fsList.c_str());
   }
}
}

void brw_results_callback(Fl_Widget *, void *) {
  if (brw_results->value())
{
   select_results = brw_results->text(brw_results->value());
   if ( option_type.length() > 0 )
   {
     string command = "sed -i '/" + select_results + "/d' " + copy2fsList;
     system(command.c_str());
     brw_results->load(copy2fsList.c_str());
   }
}
}

Fl_Menu_Item menu_[] = {
 {"Dependencies", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Build Dependencies Database", 0,  (Fl_Callback*)depends_callback, (void*)("builddb"), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"List Dependencies", 0,  (Fl_Callback*)depends_callback, (void*)("dependson"), 1, FL_NORMAL_LABEL, 0, 14, 0},
 {"LIst Required By", 0,  (Fl_Callback*)depends_callback, (void*)("requiredby"), 1, FL_NORMAL_LABEL, 0, 14, 0},
 {"List Missing Dependencies", 0,  (Fl_Callback*)depends_callback, (void*)("audit"), 1, FL_NORMAL_LABEL, 0, 14, 0},
 {"Display All with No Dependencies", 0,  (Fl_Callback*)depends_callback, (void*)("nodepends"), 1, FL_NORMAL_LABEL, 0, 14, 0},
 {"Display All with Missing Dependencies", 0,  (Fl_Callback*)depends_callback, (void*)("auditall"), 1, FL_NORMAL_LABEL, 0, 14, 0},
 {"Mark for Deletion", 0,  (Fl_Callback*)depends_callback, (void*)("delete"), 1, FL_NORMAL_LABEL, 0, 14, 0},
 {"Display Marked for Deletion", 0,  (Fl_Callback*)depends_callback, (void*)("display_marked"), 1, FL_NORMAL_LABEL, 0, 14, 0},
 {"Quit", 0,  (Fl_Callback*)depends_callback, (void*)("quit"), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Install Options", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Toggle Default Copy Install", 0,  (Fl_Callback*)options_callback, (void*)("default"), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Selective Copy Install", 0,  (Fl_Callback*)options_callback, (void*)("select"), 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

Fl_Box *box_extensions=(Fl_Box *)0;

Fl_Box *box_results=(Fl_Box *)0;

Fl_Browser *brw_results=(Fl_Browser *)0;

Fl_Browser *brw_extn=(Fl_Browser *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(675, 375, "AppsAudit");
    w = o;
    o->callback((Fl_Callback*)options_callback, (void*)("quit"));
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 685, 20);
      o->menu(menu_);
    } // Fl_Menu_Bar* o
    { box_extensions = new Fl_Box(0, 24, 200, 16, "Extensions");
      box_extensions->labelfont(1);
      box_extensions->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    } // Fl_Box* box_extensions
    { box_results = new Fl_Box(225, 24, 430, 16, "Results");
      box_results->labelfont(1);
    } // Fl_Box* box_results
    { brw_results = new Fl_Browser(225, 45, 430, 325);
      brw_results->type(1);
      brw_results->textfont(4);
      brw_results->callback((Fl_Callback*)brw_results_callback);
    } // Fl_Browser* brw_results
    { brw_extn = new Fl_Browser(0, 45, 200, 325);
      brw_extn->type(1);
      brw_extn->textfont(4);
      brw_extn->callback((Fl_Callback*)brw_extn_callback);
    } // Fl_Browser* brw_extn
    o->end();
    o->resizable(o);
  } // Fl_Double_Window* o
  ifstream tcedir_file("/opt/.tce_dir");
getline(tcedir_file,tcedir);
tcedir_file.close();
copy2fsList = tcedir + "/copy2fs.lst";
copy2fsFlag = tcedir + "/copy2fs.flg";

option_type.empty();
report_type.empty();

int results = system("ls /tmp/tce.db >/dev/null 2>&1");
if (results == 0)
{
  brw_extn->load("/tmp/tce.lst");
  menu_nodepends->activate();
  menu_auditall->activate();
  menu_marked->activate();
}
  w->show(argc, argv);
  return Fl::run();
}
