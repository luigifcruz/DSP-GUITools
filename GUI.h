#ifndef _GUI_H_
#define _GUI_H_

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

class GUI {
  public:
    Display *d;
    Window w;
    XEvent e;
    GC gc;
    int s;

    void init(int w, int h);
    void draw_point(int x1, int x2);
    void draw_text(char* msg);
    void close();
    void clear();
};

#endif
