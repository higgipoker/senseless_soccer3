#pragma once
#include <SFML/Window/Event.hpp>
class Interactable {
   public:
    //
    //
    //
    virtual void OnInteract(const sf::Event &event) = 0;
};

//
//
//
class Interaction {
   public:
    //
    //
    //
    void Interact(const sf::Event &event);
    //
    //
    //
    void Connect(Interactable *i);
    int id;

   private:
    Interactable *interaction = nullptr;
};
