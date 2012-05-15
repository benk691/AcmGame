SUBDIRS=common controller effects game resources testbestbench
CLEANDIRS=$(SUBDIRS:%=clean-%)
TARGET=game.o

all: $(TARGET)

$(TARGET): $(SUBDIRS)

$(SUBDIRS):
	@( cd $@ && $(MAKE) )

clean: $(CLEANDIRS)
	rm -rf *.o *~ $(TARGET) #*

$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: all clean $(TARGET) $(OBJS) $(SUBDIRS) $(CLEANDIRS)

