#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include <vector>

//This is really a strongly typed enum
//Whenever you request the status of a key, use one of these values as the argument.
//Please use the actual name, not the number.
//These are just names.  They carry no significance beyond how you use them.
//If you need another key name, go ahead and add it.
//Just make sure every key has its own number and never change existing numbers.
struct Key
{
    #define SCI static const int
    SCI moveForward = 0;
    SCI moveBackward = 1;
    SCI moveLeft = 2;
    SCI moveRight = 3;
    SCI turnLeft = 4;
    SCI turnRight = 5;
    SCI fast = 6; // boost/sprint
    SCI slow = 7; // brake/crouch
    SCI attack1 = 8;
    SCI attack2 = 9;
    SCI attack3 = 10;
    SCI attack4 = 11;
    SCI attack5 = 12;
    SCI attack6 = 13;
    SCI attack7 = 14;
    SCI attack8 = 15;
    SCI attack9 = 16;
    SCI attack10 = 17;
    SCI jump = 18;
    SCI flyUp = 19;
    SCI flyDown = 20;
    SCI lookUp = 21;
    SCI lookDown = 22;
    SCI lookLeft = 23;
    SCI lookRight = 24;
    SCI pause = 25;
    SCI chat = 26;
    SCI map = 27;
    SCI quit = 28;
    SCI leftDoor = 29;
    SCI rightDoor = 30;
    SCI car2moveForward = 31;
    SCI car2moveBackward = 32;
    SCI car2turnLeft = 33;
    SCI car2turnRight = 34;
    SCI car2leftDoor = 35;
    SCI car2rightDoor = 36;
    
    #undef SCI
};

//Immutable class representing a key or mouse button
//To construct a PhysicalKey, pass the value glut uses for the key along with its type to the constructor.
//For example, for the A key use PhysicalKey('A', PhysicalKey::NORMAL_KEY).
//Note that 'A' is not the same as 'a'.
//For nonalphanumeric keys, use PhysicalKey::SPECIAL_KEY as the type and use glut's enum value for the value.
//For mouse buttons, use the glut enum value and PhysicalKey::MOUSE_BUTTON.
//This will ordinarily just be used as a key for the keymap.
class PhysicalKey
{
    int v;
    int t;
public:
    PhysicalKey(int glutVal, int type)
        : v(glutVal), t(type)
    {}
    
    int type() const
    {
        return t;
    }
    
    int glutVal() const
    {
        return v;
    }
    
    bool operator <(const PhysicalKey& rhs) const
    {
        if(t != rhs.t) return t < rhs.t;
        return v < rhs.v;
    }
    
    bool operator ==(const PhysicalKey& rhs) const
    {
        return t == rhs.t && v == rhs.v;
    }
};

//use these as arguments for the type parameter of the constructor
static const int NORMAL_KEY = 0;
static const int SPECIAL_KEY = 1;
static const int MOUSE_BUTTON = 2;


class Input
{
    typedef int KEY;
public:
    static void initialize();      //call this exactly once
    static void nextFrame();       //call this exactly once per frame to update key presses
    
    static void mapKey(const PhysicalKey&, KEY); //maps a physical key or button to a logical Key
    static void unmapKey(const PhysicalKey&, KEY); //removes the mapping from a physical key to a specific KEY
    static void unmapKey(const PhysicalKey&); //removes all mappings from a physical key
    
    static bool down(KEY);    //returns whether the key is held
    static bool pressed(KEY); //returns whether the key was pressed during the last frame
    
    static bool isCursorLocked(); //if the cursor is unlocked, the mouse acts normally and can be used to click on buttons
    static void lockCursor();
    static void unlockCursor();
    
    //Mouse sensitivity does nothing on its own.
    //When you get mouse input, you have to multiply it by the current sensitivity value.
    //It is stored here only for convenience.
    static void setMouseSensitivity(float);
    static float getMouseSensitivity();
    
    static int mouseX(); //movement of the mouse in pixels this frame
    static int mouseY(); //relative if the cursor is locked, absolute if unlocked
    
private:
    static void updateKeyUp(const PhysicalKey&);
    static void updateKeyDown(const PhysicalKey&);
    static void updateMousePosition(int x, int y);

    friend void processNormalKeyDown(unsigned char key, int x, int y);
    friend void processNormalKeyUp(unsigned char key, int x, int y);
    friend void processSpecialKeyDown(int key, int x, int y);
    friend void processSpecialKeyUp(int key, int x, int y);
    friend void processMouseButton(int button, int state, int x, int y);
    friend void processMouseMotion(int x, int y);

    static std::multimap <PhysicalKey, KEY> keyMap;
    static std::vector <KEY> keysHeld;
    static std::vector <KEY> dirtyKeysHeld;
    static std::vector <KEY> keysPressed;
    static std::vector <KEY> dirtyKeysPressed;
    
    static bool cursorLocked;
    static float mouseSensitivity;
    
    static int x;
    static int y;
    static int dirtyX;
    static int dirtyY;
};

#endif