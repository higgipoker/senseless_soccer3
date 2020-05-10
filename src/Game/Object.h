#pragma once
#include "Message.h"
namespace Senseless{

// ***************************************************************************
// *                                                                         *
// * Object                                                                  *
// *                                                                         *
// ***************************************************************************
class Object{
   public:
    virtual void send(const MessageName in_message);
    virtual void receive(const MessageName in_message) =0;
};
// *
// *
// ***************************************************************************
}
