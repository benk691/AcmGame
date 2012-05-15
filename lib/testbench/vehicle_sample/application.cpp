//Jorge Gonzalez
//Lab 2: Line resterization
//CS 130, Spring 2012

#include "application.h"

#include <iostream>
#include <cassert>

using namespace std;


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void draw_grid();

application::application()
: solid(true), up_1(false), down_1(false), left_1(false), right_1(false),
               up_2(false), down_2(false), left_2(false), right_2(false),
               left_d1(false), right_d1(false), left_d2(false), right_d2(false)
{}

application::~application()
{}

// triggered once after the OpenGL context is initialized
void application::init_event()
{
    cout << "CAMERA CONTROLS: \n  LMB: Rotate \n  MMB: Pan \n  LMB: Dolly" << endl;
    cout << "KEYBOARD CONTROLS: \n  '=': Toggle wireframe mode" << endl;

    const GLfloat ambient[] = { 0.15, 0.15, 0.15, 1.0 };
    const GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
    const GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

    // enable a light
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glEnable(GL_LIGHT1);

    // enable depth-testing, colored materials, and lighting
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // normalize normals so lighting calculations are correct
    // when using GLUT primitives
    glEnable(GL_NORMALIZE);

    // enable smooth shading
    glShadeModel(GL_SMOOTH);

    // set the cameras default coordinates
    camera.set_distance(20);
    camera.set_elevation(35);
    camera.set_twist(45);

    t.reset();
    //
    Vehicle car_1(true,0,2.5,-3);
    Vehicle car_2(false,0,2.5,3);
    vehicles.push_back(car_1);
    vehicles.push_back(car_2);
}
// triggered each time the application needs to redraw
void application::draw_event()
{
    // apply our camera transformation
    camera.apply_gl_transform();

    // set the position of the light
    const GLfloat light_pos1[] = { 0.0, 10.0, 0.0, 1 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);

    // draws the grid and frame at the origin
    draw_grid();

    //draw the vehicles
    camera.set_focal_point(vehicles[0].x_pos,vehicles[0].y_pos + 2,vehicles[0].z_pos);

    camera.set_twist(vehicles[0].direction - 90);
    /*

    double rel_dir = vehicles[0].direction - camera.get_twist();
    if(rel_dir > 95)
        camera.set_twist(camera.get_twist() + .1);
    else if(rel_dir < 85)
        camera.set_twist(camera.get_twist() - .1);
    */

    for(unsigned int i = 0; i < vehicles.size(); ++i){
        if(vehicles[i].use_keys)
            vehicles[i].draw(t.elapsed()*180,up_1,down_1,left_1,right_1,left_d1,right_d1);
        else
            vehicles[i].draw(t.elapsed()*180,up_2,down_2,left_2,right_2,left_d2,right_d2);
    }
}
// triggered when mouse is clicked
void application::mouse_click_event(
    mouse_button button, mouse_button_state button_state,int x, int y)
{}

// triggered when mouse button is held down and the mouse is
// moved
void application::mouse_move_event(int x, int y)
{}

// triggered when a key is pressed on the keyboard
void application::keyboard_event(unsigned char key, int x, int y)
{
    if(key == '=')
        solid = !solid;

    if(key == 'w') up_1 = true;
    if(key == 's') down_1 = true;
    if(key == 'a') left_1 = true;
    if(key == 'd') right_1 = true;

    if(key == 'i') up_2 = true;
    if(key == 'k') down_2 = true;
    if(key == 'j') left_2 = true;
    if(key == 'l') right_2 = true;

    if(key == 'q') left_d1 = !left_d1;
    if(key == 'e') right_d1 = !right_d1;

    if(key == 'u') left_d2 = !left_d2;
    if(key == 'o') right_d2 = !right_d2;
}
// triggered when a key is released on the keyboard
void application::keyboard_up_event(unsigned char key, int x, int y)
{
    if(key == 'w') up_1 = false;
    if(key == 's') down_1 = false;
    if(key == 'a') left_1 = false;
    if(key == 'd') right_1 = false;

    if(key == 'i') up_2 = false;
    if(key == 'k') down_2 = false;
    if(key == 'j') left_2 = false;
    if(key == 'l') right_2 = false;
}
void draw_grid()
{
    glDisable(GL_LIGHTING);
    glLineWidth(2.0);

    //
    // Draws the coordinate frame at origin
    //
    glPushMatrix();
    glScalef(1, 1, 1);
    glBegin(GL_LINES);

    // x-axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    // y-axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    // z-axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glPopMatrix();

    //
    // Draws a grid along the x-z plane
    //
    glLineWidth(1.0);
    glColor3f(.20, .20, .20);
    glBegin(GL_LINES);

    int ncells = 100;
    int ncells2 = ncells/2;

    for (int i= 0; i <= ncells; i++)
    {
        int k = -ncells2;
        k +=i;
        glVertex3f(ncells2,0,k);
        glVertex3f(-ncells2,0,k);
        glVertex3f(k,0,ncells2);
        glVertex3f(k,0,-ncells2);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}
