CXX=g++
CPPFLAGS=-std=c++11 -Wall -O3
LDLIBS=-L/opt/X11/lib -lX11 -lpthread

SRCS=GUI.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: constellation bitviewer clean

bitviewer: $(OBJS)
	$(CXX) $(CPPFLAGS) bitviewer.cpp -o bitviewer $(OBJS) $(LDLIBS) 

constellation: $(OBJS)
	$(CXX) $(CPPFLAGS) constellation.cpp -o constellation $(OBJS) $(LDLIBS) 

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f constellation bitviewer
