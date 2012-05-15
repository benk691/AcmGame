CXX=g++
CXXFLAGS=-g -Wall
CPPFLAGS = -Wall -g
LIBS  = -lGL -lGLU -lglut
#LIBS = -lmingw32 -lglut32 -lopengl32 -lglu32

export CXX
export CXXFLAGS
export CPPFLAGS
export LIBS

OBJS=bin/main.o
SUBDIRS=bin lib
CLEANDIRS=$(SUBDIRS:%=clean-%)
TARGET=play

all: $(TARGET)

$(TARGET): $(SUBDIRS)

$(SUBDIRS):
	@( cd $@ && $(MAKE) )

clean: $(CLEANDIRS)
	rm -rf *.o *~ $(TARGET) #*

$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: all clean $(TARGET) $(OBJS) $(SUBDIRS) $(CLEANDIRS)

