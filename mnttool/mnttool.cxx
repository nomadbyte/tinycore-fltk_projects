// generated by Fast Light User Interface Designer (fluid) version 1.0109

#include "mnttool.h"
// (c) Robert Shingledecker 2008
#include <iostream>
#include <fstream>
#include <vector>
static int cycle; 
static int size; 
static int selected; 
using namespace std;
vector<string> mountList; 
static vector<int> mountState; 

int getMountables() {
  mountList.clear();
mountState.clear();

system("/usr/bin/mountables.sh");

ifstream fin("/tmp/mountables");
string line;
string commandHead = "grep /mnt/";
string commandTail = " /etc/mtab >/dev/null";

while ( getline(fin,line) )
{
   mountList.push_back(line);
   mountState.push_back(system((commandHead + line + commandTail).c_str()));
}   
fin.close();

size = mountList.size();
cycle = 0;
btnDevice->label(mountList[0].c_str());
if ( mountState[0] == 0)
{  
   btnState->label("Mounted");
   btnState->color((Fl_Color)2);
} else
{
   btnState->label("Unmounted");
   btnState->color((Fl_Color)1);
}      
selected = 0;
}

void btnCallback(Fl_Widget*, void* userdata) {
  if (userdata == "device")
{
   cycle++;
   if (cycle >= size)
       getMountables();

   btnDevice->label(mountList.at(cycle).c_str());
   if ( mountState[cycle] == 0)
   {  
      btnState->label("Mounted");
      btnState->color((Fl_Color)2);
   } else
   {
      btnState->label("Unmounted");
      btnState->color((Fl_Color)1);      
   }      
   selected = cycle;
}
       
if (userdata == "state")
{
   int results;
   if (mountState.at(selected) == 0)   // mounted
   {
      results = system(("sudo umount /dev/" + mountList.at(selected)).c_str());
      if (results == 0)
      {
         btnState->label("Unmounted");
         btnState->color((Fl_Color)1);         
         btnState->redraw_label();        
         mountState.at(selected)=256;
      }    
   }   
   else
   {
      results = system(("sudo mount /dev/" + mountList.at(selected)).c_str());
      if (results == 0)
      {
         btnState->label("Mounted");
         btnState->color((Fl_Color)2);         
         btnState->redraw_label();        
         mountState.at(selected)=0;
         cout << "after mount" << endl;
      }
   }
}
}

Fl_Button *btnDevice=(Fl_Button *)0;

Fl_Button *btnState=(Fl_Button *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(80, 45);
    w = o;
    { btnDevice = new Fl_Button(0, 0, 80, 20, "button");
      btnDevice->callback((Fl_Callback*)btnCallback, (void*)("device"));
    } // Fl_Button* btnDevice
    { btnState = new Fl_Button(0, 25, 80, 20, "button");
      btnState->callback((Fl_Callback*)btnCallback, (void*)("state"));
    } // Fl_Button* btnState
    o->end();
  } // Fl_Double_Window* o
  getMountables();
  w->show(argc, argv);
  return Fl::run();
}
