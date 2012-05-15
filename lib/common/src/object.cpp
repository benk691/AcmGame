#include "../include/object.h"

unsigned int Object::curObjId = 0;

Object::Object()
    :x(0.0), y(0.0), z(0.0), pitch(0.0), roll(0.0), yaw(0.0), objId(++curObjId)
{ std::cout << "\ncurObjId = " << curObjId << "\n"; }

// ---------- Test ----------

class Thing : public Object
{
    public:
        Thing() {}

        virtual ~Thing() {}

        virtual void draw() {}

        virtual void update() {}
};

int main()
{
    Thing thing1;
    Thing thing2;
    return 0;
}
