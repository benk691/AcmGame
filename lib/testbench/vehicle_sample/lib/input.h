#ifndef INPUT_H_
#define INPUT_H_

//-----------------------------------------------------------------------------------------------------------
// How to use this file
//-----------------------------------------------------------------------------------------------------------
//
// This file wraps the input provided by GLUT.  Instead of checking if a certain key on the keyboard is held, 
// you check a certain "logical key."  One physical key is W, while its logical key might be Key::moveForward.
// This allows the keys to be remapped, even at runtime.
//
//-----------------------------------------------------------------------------------------------------------
// Checking for key presses
//-----------------------------------------------------------------------------------------------------------
//
// There is no way to check if a physical key is held.  All requests are made with logical keys defined in
// struct Key.
// To check if a logical key is being held, call Input::down(Key::somekey), where somekey is the name you
// want to check.  You can also check if the key was just pressed; this lasts for only one frame.  For
// example, you might use this method for attacks, so that the player has to let go and press the key again
// to attack again instead of just holding the key down.  To do this, call Input::pressed(Key::somekey).
//
//-----------------------------------------------------------------------------------------------------------
// Mapping keys
//-----------------------------------------------------------------------------------------------------------
//
// None of the logical keys will work initially.  You have to assign a physical key to each logical key you
// will use.  This is done with Input::mapKey(PhysicalKey(somekeyID, somekeyType), someLogicalKey).
// One of its arguments is an object of type PhysicalKey.  This represents an actual key on the keyboard.
// You can only use keys that GLUT represents normally.  This includes all the letters, numbers, function
// keys, and arrow keys, plus mouse buttons.  Some keys that you might expect to find, like shift, are not 
// available.  Be sure only to use lowercase letters, as the uppercase variants are actually considered 
// different keys.  If you map an uppercase letter, it will probably never trigger.
// PhysicalKey also takes a type parameter.  There are currently three choices: NORMAL_KEY, SPECIAL_KEY, and
// MOUSE_BUTTON.  NORMAL_KEY is used for letters and numbers, and the like.  The key ID for normal keys is
// an ASCII value; to register the W key, use PhysicalKey('w', NORMAL_KEY).  SPECIAL_KEY refers to
// function and arrow keys, plus possibly a few more.  The keyID for these is, for example, GLUT_F1.
// Mouse buttons are similar to function keys; use PhysicalKey(MOUSE_LEFT_BUTTON, MOUSE_BUTTON).
// Always use the correct type for the keyID you are entering.  If you use the wrong type, you might cause
// conflicts.
// 
// You can map any number of physical keys to one logical key.  Similarly, you can map multiple logical keys
// to a single physical key.
//
// You can add a key mapping at any time by calling mapKey again.  To remove an existing keymapping, use
// unmapKey(physicalkey, logicalkey) to remove a particular mapping from the physical key, or use
// unmapKey(physicalkey) to remove all of the mappings from that key.
//
//-----------------------------------------------------------------------------------------------------------
// Adding keys
//-----------------------------------------------------------------------------------------------------------
//
// If, for some reason, you feel that none of the key names in Key describe what you want a key to do, you
// can add another key name to Key.  Use the same format as the existing keys, and be sure to assign a new
// number not used by any other key.  Just make sure there isn't a similar key that other people are already
// using; you want each function to have only one logical key.
// Please ask before you add keys.  There are probably enough already.
//
//-----------------------------------------------------------------------------------------------------------
// Mouse input
//-----------------------------------------------------------------------------------------------------------
//
// At the start, the mouse cursor is locked to the screen.  This is called relative mode.
// In relative mode, you can use Input::mouseX() and Input::mouseY() to see how far the mouse has moved
// this frame.  However, whenever you do this you have to multiply the result by Input::getMouseSensitivity().
// Unfortunately, Input cannot do this for you because these functions have to return integers to be
// compatible with absolute mode.  After doing the multiplication yourself, you have a float representing how
// far the mouse moved this frame.
// In relative mode, the mouse cursor is not visible.
// If you call Input::unlockMouse(), you enter absolute mode.  In absolute mode, the mouse cursor is visible
// and moves normally.  When you check Input::mouseX() and Input::mouseY(), you get the position of the mouse
// cursor in pixels.  Use this for menus and RTS style controls, for example.
// To change the mouse sensitivity, call Input::setMouseSensitivity(float).  Note that this has no effect
// in absolute mode and you must multiply by the sensitivity yourself in relative mode.
//
//-----------------------------------------------------------------------------------------------------------
// In the game loop
//-----------------------------------------------------------------------------------------------------------
//
// You have to initialize the input system once before using it by calling Input::initialize.  After this you
// can begin mapping keys.
// You also have to call Input::nextFrame() exactly once per frame.  It doesn't matter where in the frame, but
// it has to be consistent.  This is used to cycle the double buffers so that keys don't suddenly change
// during a calculation.
//
//-----------------------------------------------------------------------------------------------------------

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
//For example, for the A key use PhysicalKey('a', PhysicalKey::NORMAL_KEY).
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
