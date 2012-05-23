#include "gl_viewer.h"

#include <cassert>
#include <iostream>

using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "lib/input.h"

gl_viewer* gl_viewer::singleton = NULL;

gl_viewer::gl_viewer()
{
    assert(!singleton); // ensure only one instance is created
    singleton = this;
}

gl_viewer::~gl_viewer()
{
    singleton = NULL;
}

void gl_viewer::init(int argc, char *argv[], int width, int height)
{
    // set up glut
    glutInit(&argc, argv);

    // create a 24-bit double-buffered window
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(width, height);
    glutCreateWindow("Skeleton environment");

    // called when Glut needs to display
    glutDisplayFunc(&gl_viewer::glut_display_event_wrapper);

    // called when GLUT has nothing to do
    glutIdleFunc(&gl_viewer::glut_display_event_wrapper);

    // called when the window is resized
    glutReshapeFunc(&gl_viewer::glut_reshape_event_wrapper);

    // clear our background to black when glClear is called
    glClearColor(0.0, 0.0, 0.0, 0);

    singleton->init_event();

    this->width = width;
    this->height = height;
    //first_click = true;

    Input::initialize();
    Input::mapKey(PhysicalKey(GLUT_KEY_F1, SPECIAL_KEY), Key::quit);

    Input::mapKey(PhysicalKey('w', NORMAL_KEY), Key::moveForward);
    Input::mapKey(PhysicalKey('s', NORMAL_KEY), Key::moveBackward);
    Input::mapKey(PhysicalKey('a', NORMAL_KEY), Key::turnLeft);
    Input::mapKey(PhysicalKey('d', NORMAL_KEY), Key::turnRight);
    Input::mapKey(PhysicalKey('q', NORMAL_KEY), Key::leftDoor);
    Input::mapKey(PhysicalKey('e', NORMAL_KEY), Key::rightDoor);
    Input::mapKey(PhysicalKey('b', NORMAL_KEY), Key::attack1);

    Input::mapKey(PhysicalKey(GLUT_KEY_UP, SPECIAL_KEY), Key::car2moveForward);
    Input::mapKey(PhysicalKey(GLUT_KEY_DOWN, SPECIAL_KEY), Key::car2moveBackward);
    Input::mapKey(PhysicalKey(GLUT_KEY_LEFT, SPECIAL_KEY), Key::car2turnLeft);
    Input::mapKey(PhysicalKey(GLUT_KEY_RIGHT, SPECIAL_KEY), Key::car2turnRight);
    Input::mapKey(PhysicalKey('u', NORMAL_KEY), Key::car2leftDoor);
    Input::mapKey(PhysicalKey('o', NORMAL_KEY), Key::car2rightDoor);
    Input::mapKey(PhysicalKey(0, MOUSE_BUTTON), Key::attack2);

    Input::mapKey(PhysicalKey('p', NORMAL_KEY), Key::pause);
}

void gl_viewer::glut_display_event_wrapper()
{
    // clear our color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // call our gl_viewers draw event and render to back buffer

    singleton->draw_event();

    // swap the back buffer with the front (user always sees front
    // buffer on display)
    glutSwapBuffers();
}

void gl_viewer::run()
{
    // pass execution to Glut. Now Glut is in control of the main loop.
    glutMainLoop();
}

void gl_viewer::glut_reshape_event_wrapper(int width, int height)
{
    singleton->width = width;
    singleton->height = height;

    // adjust the view frustrum and viewport
    // to reflect the new window dimensions
    glViewport(0, 0, width, height);

    if (height == 0) height = 1;

    // set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, width / (float)height, 0.1f, 300.0f);
    glMatrixMode(GL_MODELVIEW);
}

