#include "KitFactory.hpp"
namespace Senseless {
//
//
//
Kit KitFactory::makeDefaultRedKit() { return {KitType::Standard, {}}; }

//
//
//
Kit KitFactory::makeDefaultBlueKit() {
  return {KitType::Standard,
          {{sf::Color(135, 0, 0), sf::Color(0, 0, 135)},
           {sf::Color(175, 0, 0), sf::Color(0, 0, 175)},
           {sf::Color(215, 0, 0), sf::Color(0, 0, 215)},
           {sf::Color(255, 0, 0), sf::Color(0, 0, 255)}}};
}

}  // namespace Senseless
