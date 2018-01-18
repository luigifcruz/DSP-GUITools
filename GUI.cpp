#include "GUI.h"

void GUI::init(int width, int height) {
  d = XOpenDisplay(NULL);
  
  if (d == NULL) {
     fprintf(stderr, "Cannot open display.\n");
     exit(1);
  }
 
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, WhitePixel(d, s), BlackPixel(d, s));

  XSelectInput(d, w, ExposureMask|KeyPressMask);
  gc = XCreateGC(d, w, 0,0); 
  XStoreName(d, w, "Constellation");
  XSetBackground(d, gc, BlackPixel(d, s));
  XSetForeground(d, gc, WhitePixel(d, s));

  XClearWindow(d, w);
  XMapRaised(d, w);
  
  XSizeHints *hints = XAllocSizeHints();
  hints->flags = PMinSize|PMaxSize;
  hints->min_width = hints->max_width = width;
  hints->min_height = hints->max_height = height;
  XSetWMNormalHints(d, w, hints);
  XSetWMSizeHints(d, w, hints, PMinSize|PMaxSize);
}

void GUI::draw_text(char* msg) {
  XDrawString(d, w, gc, 10, 20, msg, strlen(msg));
}

void GUI::draw_point(int x1, int x2) {
  XFillRectangle(d, w, gc, x1, x2, 1, 1);
}

void GUI::clear() {
  XClearWindow(d, w);
}

void GUI::close() {
  XCloseDisplay(d);
}

