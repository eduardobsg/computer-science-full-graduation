#
# all our Makefiles are lovingly handcrafted by our semi-skilled technicians
#
GIMPARGS = $(shell gimptool-2.0 --cflags)
GIMPLIBS = $(shell gimptool-2.0 --libs)
# NODEPS = -DGIMP_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED
# gimp progress api changed in 2.3.something - compiles OK with this though
#NODEPS = -DGTK_DISABLE_DEPRECATED
NODEPS =
MFPATH = maxflow-v2.2.src/adjacency_list
CPPARGS = -Wall -O2 -I.

all: lazy-snapping

lazy-snapping: main.o $(MFPATH)/maxflow.o $(MFPATH)/graph.o gui.o lazy-snapping.o
	g++ -o lazy-snapping $(CPPARGS) $^ $(GIMPLIBS) $(NODEPS)

%.o : %.cpp
	g++ -c -o $@ $(CPPARGS) $(GIMPARGS) $(NODEPS) $<


install: lazy-snapping
	gimptool-2.0 --install-bin lazy-snapping

clean:
	rm -f lazy-snapping *~ *.o $(MFPATH)/*.o

