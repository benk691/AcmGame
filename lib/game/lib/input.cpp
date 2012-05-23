#include "input.h"

#include <GL/glut.h>
#include <utility>
#include <algorithm>

std::multimap <PhysicalKey, int> Input::keyMap;
std::vector <int> Input::keysHeld;
std::vector <int> Input::dirtyKeysHeld;
std::vector <int> Input::keysPressed;
std::vector <int> Input::dirtyKeysPressed;

bool Input::cursorLocked;
float Input::mouseSensitivity = 0.2f;

int Input::x;
int Input::y;
int Input::dirtyX;
int Input::dirtyY;

void processNormalKeyDown(unsigned char key, int x, int y)
{
    if(key >= 'A' && key <= 'Z') key += 'a' - 'A';
    
    switch(key)
    {
        case '!':
            key = '1';
            break;
        case '@':
            key = '2';
            break;
        case '#':
            key = '3';
            break;
        case '$':
            key = '4';
            break;
        case '%':
            key = '5';
            break;
        case '^':
            key = '6';
            break;
        case '&':
            key = '7';
            break;
        case '*':
            key = '8';
            break;
        case '(':
            key = '9';
            break;
        case ')':
            key = '0';
            break;
        case '_':
            key = '-';
            break;
        case '+':
            key = '=';
            break;
        case '{':
            key = '[';
            break;
        case '}':
            key = ']';
            break;
        case '|':
            key = '\\';
            break;
        case ':':
            key = ';';
            break;
        case '\"':
            key = '\'';
            break;
        case '<':
            key = ',';
            break;
        case '>':
            key = '.';
            break;
        case '?':
            key = '/';
            break;
        case '~':
            key = '`';
            break;
    }

    PhysicalKey pk(key, NORMAL_KEY);
    Input::updateKeyDown(pk);
}

void processNormalKeyUp(unsigned char key, int x, int y)
{
    if(key >= 'A' && key <= 'Z') key += 'a' - 'A';
    
    switch(key)
    {
        case '!':
            key = '1';
            break;
        case '@':
            key = '2';
            break;
        case '#':
            key = '3';
            break;
        case '$':
            key = '4';
            break;
        case '%':
            key = '5';
            break;
        case '^':
            key = '6';
            break;
        case '&':
            key = '7';
            break;
        case '*':
            key = '8';
            break;
        case '(':
            key = '9';
            break;
        case ')':
            key = '0';
            break;
        case '_':
            key = '-';
            break;
        case '+':
            key = '=';
            break;
        case '{':
            key = '[';
            break;
        case '}':
            key = ']';
            break;
        case '|':
            key = '\\';
            break;
        case ':':
            key = ';';
            break;
        case '\"':
            key = '\'';
            break;
        case '<':
            key = ',';
            break;
        case '>':
            key = '.';
            break;
        case '?':
            key = '/';
            break;
        case '~':
            key = '`';
            break;
    }
    PhysicalKey pk(key, NORMAL_KEY);
    Input::updateKeyUp(pk);
}

void processSpecialKeyDown(int key, int x, int y)
{
    PhysicalKey pk(key, SPECIAL_KEY);
    Input::updateKeyDown(pk);
}

void processSpecialKeyUp(int key, int x, int y)
{
    PhysicalKey pk(key, SPECIAL_KEY);
    Input::updateKeyUp(pk);
}

void processMouseButton(int button, int state, int x, int y)
{
    PhysicalKey pk(button, MOUSE_BUTTON);
    if(state == GLUT_DOWN)
        Input::updateKeyDown(pk);
    if(state == GLUT_UP)
        Input::updateKeyUp(pk);
}

void processMouseMotion(int x, int y)
{
    Input::updateMousePosition(x, y);
}

void Input::initialize()
{
    glutKeyboardFunc(processNormalKeyDown);
    glutKeyboardUpFunc(processNormalKeyUp);
    glutSpecialFunc(processSpecialKeyDown);
    glutSpecialUpFunc(processSpecialKeyUp);
    glutMouseFunc(processMouseButton);
    glutMotionFunc(processMouseMotion);
    glutPassiveMotionFunc(processMouseMotion);
    
    lockCursor();
}

void Input::nextFrame()
{
    keysHeld = dirtyKeysHeld;
    
    keysPressed.clear();
    keysPressed.swap(dirtyKeysPressed);
    
    x = dirtyX;
    y = dirtyY;
    dirtyX = 0;
    dirtyY = 0;
    
    //keep the cursor in the middle of the window if it is locked
    if(cursorLocked) glutWarpPointer(300, 300);
}

void Input::mapKey(const PhysicalKey& pk, int key)
{
    //check if the key already has this mapping
    std::multimap <PhysicalKey, int>::iterator it = keyMap.find(pk);
    while(it != keyMap.end() && it->first == pk)
    {
        if(it->second == key) return;
        ++it;
    }
    
    //map the key
    keyMap.insert(std::make_pair(pk, key));
}

void Input::unmapKey(const PhysicalKey& pk, int key)
{
    std::multimap <PhysicalKey, int>::iterator it = keyMap.find(pk);
    while(it != keyMap.end() && it->first == pk)
    {
        if(it->second == key)
        {
            keyMap.erase(it);
            return;
        }
        
        ++it;
    }
}

void Input::unmapKey(const PhysicalKey& pk)
{
    std::multimap <PhysicalKey, int>::iterator it = keyMap.find(pk);
    while(it != keyMap.end())
    {
        keyMap.erase(it);
        it = keyMap.find(pk);
    }
}

bool Input::down(int key)
{
    return std::find(keysHeld.begin(), keysHeld.end(), key) != keysHeld.end();
}

bool Input::pressed(int key)
{
    return std::find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end();
}

void Input::updateKeyUp(const PhysicalKey& pk)
{
    std::multimap <PhysicalKey, int>::iterator it = Input::keyMap.find(pk);
    while(it != keyMap.end() && it->first == pk)
    {
        std::vector <int>::iterator i = std::find(Input::dirtyKeysHeld.begin(), Input::dirtyKeysHeld.end(), it->second);
        while(i != Input::dirtyKeysHeld.end())
        {
            Input::dirtyKeysHeld.erase(i);
            //keysPressed is intentionally not updated here
            i = std::find(Input::dirtyKeysHeld.begin(), Input::dirtyKeysHeld.end(), it->second);
        }
        
        ++it;
    }
}

void Input::updateKeyDown(const PhysicalKey& pk)
{
    std::multimap <PhysicalKey, int>::iterator it = Input::keyMap.find(pk);
    while(it != Input::keyMap.end() && it->first == pk)
    {
        Input::dirtyKeysHeld.push_back(it->second);
        if(std::find(keysHeld.begin(), keysHeld.end(), it->second) == keysHeld.end())
            Input::dirtyKeysPressed.push_back(it->second);
        ++it;
    }
}

void Input::updateMousePosition(int x, int y)
{
    if(cursorLocked)
    {
        dirtyX += (x - 300);
        dirtyY += (y - 300);
    }
    else
    {
        Input::dirtyX = x;
        Input::dirtyY = y;
    }
}

int Input::mouseX()
{
    return x;
}

int Input::mouseY()
{
    return y;
}

bool Input::isCursorLocked()
{
    return cursorLocked;
}

void Input::lockCursor()
{
    if(cursorLocked) return;
    
    cursorLocked = true;
    glutSetCursor(GLUT_CURSOR_NONE);
}

void Input::unlockCursor()
{
    if(!cursorLocked) return;
    
    cursorLocked = false;
    glutSetCursor(GLUT_CURSOR_INHERIT);
}

void Input::setMouseSensitivity(float val)
{
    mouseSensitivity = val;
}

float Input::getMouseSensitivity()
{
    return Input::mouseSensitivity;
}
