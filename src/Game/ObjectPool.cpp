#include "ObjectPool.h"
//
#include "Object.h"
namespace Senseless {
std::set<Object *> ObjectPool::objects;
//
//
//
void ObjectPool::add(Object *obj) {
    objects.insert(obj);
}
//
//
//
void ObjectPool::rem(Object *obj) {
    auto o = objects.find(obj);
    if (o != objects.end()) {
        objects.erase(o);
    }
}
//
//
//
void ObjectPool::sendMessage(const MessageName &in_message) {
    for (auto &object : objects) {
        object->receive(in_message);
    }
}
}  // namespace Senseless
