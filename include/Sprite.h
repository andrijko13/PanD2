#ifndef AJSPRITE_DEFINE
#define AJSPRITE_DEFINE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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

    class Position {
        public:
            double const getX() { return this->x; };
            double const getY() { return this->y; };
            void const setX(const double &xpos) { this->x = xpos; };
            void const setY(const double &ypos) { this->y = ypos; };

        private:
            double x;
            double y;
    };

    class PhysicsBody {
        public:
            enum PhysicsBodyShape {PhysicsBodyCircle, PhysicsBodyRect};
            static PhysicsBody BodyWithCircleOfRadius(double radius);
        protected:
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

        private:
            Position position;
            int radius;

    };

}
#endif
