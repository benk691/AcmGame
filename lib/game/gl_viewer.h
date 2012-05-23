#ifndef GL_VIEWER_H
#define GL_VIEWER_H

#include <GL/glut.h>

#include "gl_camera.h"

class gl_viewer
{
    public:
        gl_viewer();
        virtual ~gl_viewer();

        virtual void init_event() {}
        virtual void draw_event() {}

        // Initializes Glut. Glut is a OpenGL helper
        // library designed to allow easy GL window creation on all
        // of the various operating system.

        void init(int argc, char *argv[], int width, int height);

        //At this point execution is controlled by glut.
        void run();

    protected:
        // window width & height
        int width, height;
        gl_camera camera;

    private:
        static void glut_display_event_wrapper();
        static void glut_reshape_event_wrapper(int width, int height);

        static gl_viewer* singleton;
};

#endif
