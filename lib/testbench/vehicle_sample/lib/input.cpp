#include "input.h"

#include <GL/glut.h>
#include <utility>
#include <algorithm>

std::multimap <PhysicalKey, int> Input::keyMap;
std::vector <int> Input::keysHeld;
std::vector <int> Input::dirtyKeysHeld;
std::vector <int> Input::keysPressed;
std::vector <int> Input::dirtyKeysPressed;

void processNormalKeyDown(unsigned char key, int x, int y)
{
    PhysicalKey pk(key, PhysicalKey::NORMAL_KEY);
    Input::updateKeyDown(pk);
}

void processNormalKeyUp(unsigned char key, int x, int y)
{
    PhysicalKey pk(key, PhysicalKey::NORMAL_KEY);
    Input::updateKeyUp(pk);
}

void processSpecialKeyDown(int key, int x, int y)
{
    PhysicalKey pk(key, PhysicalKey::SPECIAL_KEY);
    Input::updateKeyDown(pk);
}

void processSpecialKeyUp(int key, int x, int y)
{
    PhysicalKey pk(key, PhysicalKey::SPECIAL_KEY);
    Input::updateKeyUp(pk);
}

void processMouseButton(int button, int state, int x, int y)
{
    PhysicalKey pk(button, PhysicalKey::MOUSE_BUTTON);
    if(state == GLUT_DOWN)
        Input::updateKeyDown(pk);
    if(state == GLUT_UP)
        Input::updateKeyUp(pk);
}

void Input::initialize()
{
    glutKeyboardFunc(processNormalKeyDown);
    glutKeyboardUpFunc(processNormalKeyUp);
    glutSpecialFunc(processSpecialKeyDown);
    glutSpecialUpFunc(processSpecialKeyUp);
    glutMouseFunc(processMouseButton);
    
    glutSetCursor(GLUT_CURSOR_NONE);
}

void Input::nextFrame()
{
    //std::vector <int> result(keysHeld.size() + dirtyKeysHeld.size());
    //std::sort(keysHeld.begin(), keysHeld.end());
    //std::sort(dirtyKeysHeld.begin(), dirtyKeysHeld.end());
    //std::set_union(keysHeld.begin(), keysHeld.end(), dirtyKeysHeld.begin(), dirtyKeysHeld.end(), result.begin());
    //keysHeld.swap(result);
    //dirtyKeysHeld = keysHeld; //the dirty buffer for keys held begins with the current copy of keys held
    keysHeld = dirtyKeysHeld;
    
    keysPressed.clear();
    keysPressed.swap(dirtyKeysPressed);
    
    glutWarpPointer(300, 300);
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
    std::vector <int>::iterator i = std::find(Input::dirtyKeysHeld.begin(), Input::dirtyKeysHeld.end(), it->second);
    while(i != Input::dirtyKeysHeld.end())
    {
        Input::dirtyKeysHeld.erase(i);
        //keysPressed is intentionally not updated here
        i = std::find(Input::dirtyKeysHeld.begin(), Input::dirtyKeysHeld.end(), it->second);
    }
}

void Input::updateKeyDown(const PhysicalKey& pk)
{
    std::multimap <PhysicalKey, int>::iterator it = Input::keyMap.find(pk);
    while(it != Input::keyMap.end() && it->first == pk)
    {
        Input::dirtyKeysHeld.push_back(it->second);
        Input::dirtyKeysPressed.push_back(it->second);
        ++it;
    }
}