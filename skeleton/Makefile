CXX = g++
CXXFLAGS = -O3
CPPFLAGS = -Wall -g
LIBS  = -lGL -lGLU -lglut
#LIBS = -lmingw32 -lglut32 -lopengl32 -lglu32
OBJS  = gl_viewer.o gl_camera.o main.o application.o timer.o lib/door.o lib/vehicle.o
SRCS = gl_viewer.cpp gl_camera.cpp main.cpp application.cpp timer.cpp lib/door.cpp lib/vehicle.cpp
TARGET = transform

#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $<

#a1:	$(OBJS)
#	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

a1:	$(OBJS)
	$(CXX) $(CXXLFAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f *.o lib/*.o $(TARGET)

gl_viewer.o: gl_viewer.h gl_camera.h vector3.h
main.o: application.h gl_viewer.h vector3.h
application.o: application.h gl_viewer.h gl_camera.h vector3.h lib/door.h lib/vehicle.h
timer.o: timer.h