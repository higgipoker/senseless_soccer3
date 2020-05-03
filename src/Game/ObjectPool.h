
#pragma once
#include "Message.h"//

#include <set>
namespace Senseless {
class Object;

// ***************************************************************************
// *                                                                         *
// * ObjectPool                                                              *
// *                                                                         *
// ***************************************************************************
class ObjectPool {
    public:
    static void add            (Object *obj);
    static void sendMessage    (const MessageName &in_message);
    private:
    static std::set<Object*> objects;
};
// *
// *
// ***************************************************************************
}  // namespace Senseless
