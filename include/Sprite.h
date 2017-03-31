#ifndef AJSPRITE_DEFINE
#define AJSPRITE_DEFINE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ajx/vec2d.h>
#include "common.h"
#include <string>

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
        friend class Sprite;
        friend class Engine;

        public:
            enum PhysicsBodyShape {PhysicsBodyCircle, PhysicsBodyRect};
            static PhysicsBody BodyWithCircleOfRadius(double radius);
            PhysicsBody() : width(1.0), height(1.0), radius(1.0), mass(1.0) { };
            ~PhysicsBody() { };
            double mass;
        private:
            PhysicsBodyShape shape;
            double width;
            double height;
            double radius;
    };

    class Sprite {
        friend class Engine;

        public:


            // METHODS
            Sprite();
            ~Sprite();

            void applyForce(const Force &f);
            void applyImpulse(const Impulse &i);
            void clearForce();


            // iVARS

            PhysicsBody physicsBody;
            Position    position;
            Size        size;
            std::string name;
            bool        dynamic;
        private:
            Force userForce;
            Impulse userImpulse;

            Velocity vel;
    };

    typedef std::shared_ptr<Sprite> SpritePtr;

}
#endif
