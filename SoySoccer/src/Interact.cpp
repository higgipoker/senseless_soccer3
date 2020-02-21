#include "Interact.hpp"
//
//
//
void Interaction::Interact(const sf::Event &event) {
    if(interaction){
        interaction->OnInteract(event);
    }
}
//
//
//
void Interaction::Connect(Interactable *i){
    interaction = i;
}
