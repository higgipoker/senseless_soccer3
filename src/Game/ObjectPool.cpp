#include "ObjectPool.h"
//
#include "Object.h"
namespace Senseless {
std::set<Object*>ObjectPool::objects;
//
//
//
void ObjectPool::add(Object *obj) {
    objects.insert(obj);
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
