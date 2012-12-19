// generated by Fast Light User Interface Designer (fluid) version 1.0109

#include "stats.h"
// (c) Robert Shingledecker 2008
#include <iostream>
using namespace std;

Fl_Browser *cpuBrowser=(Fl_Browser *)0;

Fl_Browser *memBrowser=(Fl_Browser *)0;

Fl_Browser *netBrowser=(Fl_Browser *)0;

Fl_Browser *modulesBrowser=(Fl_Browser *)0;

Fl_Browser *pciBrowser=(Fl_Browser *)0;

Fl_Browser *processesBrowser=(Fl_Browser *)0;

Fl_Browser *dmesgBrowser=(Fl_Browser *)0;

Fl_Browser *mountsBrowser=(Fl_Browser *)0;

Fl_Browser *filesystemsBrowser=(Fl_Browser *)0;

Fl_Browser *bootBrowser=(Fl_Browser *)0;

Fl_Browser *extensionsBrowser=(Fl_Browser *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(610, 355, "Tiny Core System Stats");
    w = o;
    { Fl_Tabs* o = new Fl_Tabs(0, 0, 610, 356);
      o->selection_color((Fl_Color)228);
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "cpu");
        o->user_data((void*)("cpu"));
        o->hide();
        { cpuBrowser = new Fl_Browser(0, 0, 610, 335);
          cpuBrowser->textfont(4);
        } // Fl_Browser* cpuBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "mem");
        o->hide();
        { memBrowser = new Fl_Browser(0, 0, 610, 335);
          memBrowser->textfont(4);
        } // Fl_Browser* memBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 336, "net");
        o->hide();
        { netBrowser = new Fl_Browser(0, 0, 610, 335);
          netBrowser->textfont(4);
        } // Fl_Browser* netBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "modules");
        o->hide();
        { modulesBrowser = new Fl_Browser(0, 0, 610, 335);
          modulesBrowser->textfont(4);
        } // Fl_Browser* modulesBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "pci");
        o->hide();
        { pciBrowser = new Fl_Browser(0, 0, 610, 335);
          pciBrowser->textfont(4);
        } // Fl_Browser* pciBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "processes");
        o->hide();
        { processesBrowser = new Fl_Browser(0, 0, 610, 335);
          processesBrowser->textfont(4);
        } // Fl_Browser* processesBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "dmesg");
        o->hide();
        { dmesgBrowser = new Fl_Browser(0, 0, 610, 335);
          dmesgBrowser->textfont(4);
        } // Fl_Browser* dmesgBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "mounts");
        o->hide();
        { mountsBrowser = new Fl_Browser(0, 0, 610, 335);
          mountsBrowser->textfont(4);
        } // Fl_Browser* mountsBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "filesystems");
        o->hide();
        { filesystemsBrowser = new Fl_Browser(0, 0, 610, 335);
          filesystemsBrowser->textfont(4);
        } // Fl_Browser* filesystemsBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "boot");
        o->hide();
        { bootBrowser = new Fl_Browser(0, 0, 610, 335);
          bootBrowser->textfont(4);
        } // Fl_Browser* bootBrowser
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 610, 335, "extensions");
        { extensionsBrowser = new Fl_Browser(0, 0, 610, 335);
          extensionsBrowser->textfont(4);
        } // Fl_Browser* extensionsBrowser
        o->end();
      } // Fl_Group* o
      o->end();
    } // Fl_Tabs* o
    o->end();
  } // Fl_Double_Window* o
  system("cat /proc/cpuinfo|tee -a stats.txt > /tmp/stats.txt");
cpuBrowser->load("/tmp/stats.txt");
system("cat /proc/meminfo|tee -a stats.txt > /tmp/stats.txt");
memBrowser->load("/tmp/stats.txt");
system("cat /etc/resolv.conf > /tmp/stats.txt");               
system("ifconfig >> /tmp/stats.txt");                          
system("cat /tmp/stats.txt >> stats.txt");
netBrowser->load("/tmp/stats.txt");
system("cat /proc/modules | tee /tmp/stats.txt >> stats.txt");
modulesBrowser->load("/tmp/stats.txt");
system("lspci | tee /tmp/stats.txt  >> stats.txt");
pciBrowser->load("/tmp/stats.txt");
system("ps ax | tee /tmp/stats.txt >> stats.txt");
processesBrowser->load("/tmp/stats.txt");
system("dmesg  | tee /tmp/stats.txt >> stats.txt");
dmesgBrowser->load("/tmp/stats.txt");
system("mount | tee /tmp/stats.txt  >> stats.txt");
mountsBrowser->load("/tmp/stats.txt");
system("df -h | tee /tmp/stats.txt >> stats.txt");
filesystemsBrowser->load("/tmp/stats.txt");
system("sed 's/ /\\n/g' /proc/cmdline | tee /tmp/stats.txt >> stats.txt");
bootBrowser->load("/tmp/stats.txt");
system("ls -1 /usr/local/tce.installed | sort -f | tee /tmp/stats.txt >> stats.txt");
extensionsBrowser->load("/tmp/stats.txt");
  w->show(argc, argv);
  return Fl::run();
}
