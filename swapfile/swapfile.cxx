// generated by Fast Light User Interface Designer (fluid) version 1.0109

#include "swapfile.h"
// (c) Robert Shingledecker 2008
#include <iostream>
#include <sstream>
#include <string>
#include <Fl/fl_ask.H>
using namespace std;

void btn_callback(Fl_Widget*, void* userdata) {
  if (userdata == "cancel")
   exit(1);
string str_mount = inp_mount->value();
if ( str_mount == "" )
   return;
string str_size = inp_size->value();
if (str_size == "")
   return;
   
int size;
istringstream ins;
ins.str(str_size);
ins >> size;   

if ( size < 1 )
   return;
   
string command = "sudo dd if=/dev/zero of=" + str_mount + "/tc.swp bs=1024 count=" + str_size; 
if ( fl_ask(command.c_str()) )
{
   system(command.c_str());
   system( ("sudo mkswap " + str_mount + "/tc.swp").c_str());
   system( ("sudo swapon " + str_mount + "/tc.swp").c_str());
   exit(0);
}
}

Fl_Input *inp_mount=(Fl_Input *)0;

Fl_Input *inp_size=(Fl_Input *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(275, 105, "Make tc.swap EXT2 Swapfile");
    w = o;
    { inp_mount = new Fl_Input(130, 11, 135, 24, "Mounted Partition:");
    } // Fl_Input* inp_mount
    { inp_size = new Fl_Input(130, 41, 55, 24, "tc.swp in k bytes:");
    } // Fl_Input* inp_size
    { Fl_Button* o = new Fl_Button(65, 75, 64, 20, "&Cancel");
      o->callback((Fl_Callback*)btn_callback, (void*)("cancel"));
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(140, 75, 64, 20, "&Proceed");
      o->callback((Fl_Callback*)btn_callback, (void*)("proceed"));
    } // Fl_Button* o
    o->end();
  } // Fl_Double_Window* o
  w->show(argc, argv);
  return Fl::run();
}
