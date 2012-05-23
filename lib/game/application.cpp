//ACM GameDev Spring 2012

#include "application.h"

#include <iostream>
#include <cassert>

using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "lib/input.h"
#define PI 3.14159265358979323846264338328

void draw_terrain();

application::application(): prev_time(0.0){}

application::~application(){}

// triggered once after the OpenGL context is initialized
void application::init_event()
{
    //cout << "CAMERA CONTROLS: \n  LMB: Rotate \n  MMB: Pan \n  LMB: Dolly" << endl;
    //cout << "KEYBOARD CONTROLS: \n  '=': Toggle wireframe mode" << endl;
    cout << "CONTROLS:\n WASD: move \n QE: open doors \n F1: quit" << endl;

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
    glShadeModel(GL_FLAT);

    // set the cameras default coordinates
    camera.set_distance(50);//originally 20
    camera.set_elevation(45);
    camera.set_twist(0);

    t.reset();
    //
    Robot bot_1(true,0,2.5,-3);
    Robot bot_2(false,0,2.5,3);
    robots.push_back(bot_1);
    robots.push_back(bot_2);
}
// triggered each time the application needs to redraw
void application::draw_event()
{
    Input::nextFrame();
    if(Input::down(Key::quit)) exit(0);

    // set the position of the light
    const GLfloat light_pos1[] = { robots[0].x_pos, 5.0, robots[0].z_pos, 1 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);

    // apply our camera transformation
    camera.apply_gl_transform();

    // draws the terrain and frame at the origin
    draw_terrain();

    //focus camera to the robot
    //camera.set_focal_point(robots[0].x_pos + 3.2 * cos(robots[0].direction * PI / 180.0),robots[0].y_pos + 2,robots[0].z_pos + 3.2 * -sin(robots[0].direction * PI / 180.0));
    camera.set_focal_point((robots[0].x_pos + robots[1].x_pos)/2,
                           (robots[0].y_pos + robots[1].y_pos)/2,
                           (robots[0].z_pos + robots[1].z_pos)/2);

    //manual camera positioning
    //camera.add_twist(Input::mouseX()*Input::getMouseSensitivity());
    //camera.add_elevation(Input::mouseY()*Input::getMouseSensitivity());

    //automatic camera positioning
    //camera.try_twist(robots[0].direction + robots[0].turn);
    //camera.try_distance(robots[0].speed);

    for(unsigned int i = 0; i < robots.size(); ++i){
        if(robots[i].use_keys)
            robots[i].draw(t.elapsed()*180, Input::down(Key::moveForward),
                                            Input::down(Key::moveBackward),
                                            Input::down(Key::turnLeft),
                                            Input::down(Key::turnRight),
                                            Input::pressed(Key::leftDoor),
                                            Input::pressed(Key::rightDoor),
                                            Input::pressed(Key::attack1));
        else
            robots[i].draw(t.elapsed()*180, Input::down(Key::car2moveForward),
                                            Input::down(Key::car2moveBackward),
                                            Input::down(Key::car2turnLeft),
                                            Input::down(Key::car2turnRight),
                                            Input::pressed(Key::car2leftDoor),
                                            Input::pressed(Key::car2rightDoor),
                                            Input::pressed(Key::attack2));
    }

    if(robots.size() == 2){
        double x_diff = robots[0].x_pos - robots[1].x_pos;
        double z_diff = robots[0].z_pos - robots[1].z_pos;
        double y_diff = abs(robots[0].y_pos - robots[1].y_pos);

        double dist_sq = x_diff*x_diff + z_diff*z_diff;
        camera.try_distance(.0001*dist_sq);
        //std::cout << dist_sq << std::endl;
        if(dist_sq < 25 and y_diff < 8){
            robots[0].collision();
            if(robots[1].attacking())
                robots[0].snap_item();

            robots[1].collision();
            if(robots[0].attacking())
                robots[1].snap_item();
        }
    }
    //this limits the frames per second
    usleep(max((int)(1000 - (t.elapsed() - prev_time)), 0));
    prev_time = t.elapsed();
}

void draw_terrain()
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

    int ncells = 80;
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
