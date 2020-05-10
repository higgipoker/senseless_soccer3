#include "Engine/Compass.hpp"
#include "Engine/Vector.hpp"

#include <SFML/Graphics/Rect.hpp>
namespace Senseless {
class DribblePattern {
   public:
    virtual Compass nextDirection(Vector3 in_current_pos, Vector3 in_current_velocity) = 0;
    virtual bool    changeDirection()                                                  = 0;
    void            correctCourse(const Vector3 in_target) {
        if (correcting_target.magnitude2d()) {
            return;
        }
        correcting_target = in_target;
    }
    bool correcting() {
        return correcting_target.magnitude2d() == 0 ? false : true;
    }

   protected:
    int     count = 0;
    Vector3 correcting_target;
};
class DribblePatternRandom : public DribblePattern {
   public:
    //
    //
    //
    Compass nextDirection(Vector3 in_current_pos, Vector3 in_current_velocity) override {
        if (correcting_target.magnitude2d()) {
            if (in_current_pos.isMovingTowards(correcting_target, in_current_velocity)) {
                correcting_target.reset();
            }
        }

        if (correcting_target.magnitude2d() > 0) {
            in_current_velocity.rotate(-45);
        } else if (correcting_target.magnitude2d() < 0) {
            in_current_velocity.rotate(45);
        } else {
            in_current_velocity.rotate(static_cast<float>(rand() % 2 == 1 ? 45 : -45));
        }
        Compass dir(in_current_velocity);
        return dir;
    }
    //
    //
    //
    bool changeDirection() override {
        if (correcting_target.magnitude2d())
            return true;
        static const int min = 60;
        if (++count > min) {
            if (rand() % 100 > 45) {
                count = 0;
                return true;
            }
        }
        return false;
    }
};
}  // namespace Senseless
