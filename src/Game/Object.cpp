#include "Object.h"
#include "ObjectPool.h"
namespace Senseless{
//
//
//
void Object::send(const MessageName in_message){
    ObjectPool::sendMessage(in_message);
}
}
