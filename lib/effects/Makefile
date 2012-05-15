INCLUDE=
SRC=
OBJS=
SUBDIRS=include src
CLEANDIRS=$(SUBDIRS:%=clean-%)
TARGET=effects.o

all: $(TARGET)

$(TARGET): $(INCLUDE)
	$(CXX) $(CXXLFAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean: $(CLEANDIRS)
	rm -rf *.o *~ $(TARGET) #*

$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: all clean $(TARGET) $(OBJS) $(SUBDIRS) $(CLEANDIRS)
