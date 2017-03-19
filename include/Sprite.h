#ifndef AJSPRITE_DEFINE
#define AJSPRITE_DEFINE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ajx/vec2d.h>

/*
 * This class is used to create generic sprites. These should conform to typical Sprite protocol,
 * and must therefore implement features such as collision detection, impulse generation, and
 * basic kinematic properties for rigid bodies with circular physics bodies.
 *
 *
 *
 *
 *
 *
 *
 *
 *
*/

namespace pand2 {

    class PhysicsBody {
        public:
            enum PhysicsBodyShape {PhysicsBodyCircle, PhysicsBodyRect};
            static PhysicsBody BodyWithCircleOfRadius(double radius);
            PhysicsBody() : width(0), height(0), radius(0) { };
            ~PhysicsBody() { };
        private:
            PhysicsBodyShape shape;
            double width;
            double height;
            double radius;
    };

    class Sprite {

        public:


            // METHODS
            Sprite();
            ~Sprite();


            // iVARS
            int getRadius() {
                return this->radius;
            }

            void setRadius(double r) {
                this->radius = r;
            }

        private:
            ajx::vec2d<double> position;
            double radius;

    };

}
#endif
