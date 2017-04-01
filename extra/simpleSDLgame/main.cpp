#include "InitSDL.h"
#include "LTexture.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <time.h>
#include <thread>
#include <chrono>

#include <pand2/Sprite.h>
#include <pand2/Engine.h>
#include <ajx/vec2d.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum ATEXTURES {
    TEXTUREUP,
    TEXTUREDOWN,
    TEXTURELEFT,
    TEXTURERIGHT,
    TEXTUREFOO,
    TEXTUREBACKGROUND,
    TEXTUREFINAL,
    TEXTURESUM,
};

pand2::SpritePtr redBall;
pand2::Position oldpos;

bool loadTextures(LTexture *textures, const SDL &sdl) {
    bool success = true;
    if (!textures[TEXTUREUP].loadFromFile("resources/up.png")) success = false;
    if (!textures[TEXTUREDOWN].loadFromFile("resources/down.png")) success = false;
    if (!textures[TEXTURELEFT].loadFromFile("resources/left.png")) success = false;
    if (!textures[TEXTURERIGHT].loadFromFile("resources/right.png")) success = false;
    if (!textures[TEXTUREFOO].loadFromFile("resources/foo.png")) success = false;
    if (!textures[TEXTUREBACKGROUND].loadFromFile("resources/background.png")) success = false;
    if (!textures[TEXTUREFINAL].loadFromFile("resources/dots.png")) success = false;

    return success;
}

void runEventLoop(const SDL &sdl, LTexture *textures) {
    bool quit = false;
    SDL_Event e;

    SDL_Rect clips[4] = { {0,0,100,100},
                        {100,0,100,100},
                        {0,100,100,100},
                        {100,100,100,100} };

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            switch( e.type ){
                    /* Keyboard event */
                    /* Pass the event data onto PrintKeyInfo() */
                    case SDL_KEYDOWN:
                        switch( e.key.keysym.sym ){
                            case SDLK_LEFT:
                                std::cout << "left pressed" << std::endl;
                                redBall->applyImpulse(pand2::ImpulseMake(-10.0,0.0));
                                break;
                            case SDLK_RIGHT:
                                std::cout << "right pressed" << std::endl;
                                redBall->applyImpulse(pand2::ImpulseMake(10.0,0.0));
                                break;
                            case SDLK_UP:
                                std::cout << "up pressed" << std::endl;
                                redBall->applyImpulse(pand2::ImpulseMake(0.0,10.0));
                                break;
                            case SDLK_DOWN:
                                std::cout << "down pressed" << std::endl;
                                redBall->applyImpulse(pand2::ImpulseMake(0.0,-10.0));
                                break;
                            default:
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        break;

                    /* SDL_QUIT event (window close) */
                    case SDL_QUIT:
                        quit = true;
                        break;

                    default:
                        break;
                }
        }

        SDL_SetRenderDrawColor(sdl.aRenderer, 0x00, 0x00, 0x00, 0xFF);
        sdl.rClear();

        //textures[TEXTUREBACKGROUND].render(0,0);
        //textures[TEXTUREFOO].render(240,190);

        textures[TEXTUREFINAL].render(redBall->position.x()-50,SCREEN_HEIGHT - (50 + redBall->position.y()),&clips[0]);
        //textures[TEXTUREFINAL].render(SCREEN_WIDTH-clips[1].w,0,&clips[1]);
        //textures[TEXTUREFINAL].render(0,SCREEN_HEIGHT-clips[2].h,&clips[2]);
        //textures[TEXTUREFINAL].render(SCREEN_WIDTH-clips[3].w,SCREEN_HEIGHT-clips[3].h,&clips[3]);

        sdl.rPresent();
   }
}

int setUpSDL(SDL &sdl, LTexture textures[TEXTURESUM]) {
    // Here we use the SDL class to set up SDL. Nothing special here
        sdl.InitPNG(IMG_INIT_PNG);
        sdl.InitWindow("Example Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        sdl.InitRenderer(SDL_RENDERER_ACCELERATED);

        if (!sdl.SetRenderScaleQuality("1")) {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        if (!sdl.SetRenderDrawColor(0x00, 0x00, 0x00, 0xFF)) {
            std::cout << "Warning: Failed to set draw color for renderer" << std::endl;
        }

        // We want to make our game fun by adding some textures. We will store all textures in the textures array
        for (int i = 0; i < TEXTURESUM; i ++) {
            textures[i] = LTexture(sdl.aRenderer);
        }
        if (!loadTextures(textures, sdl)) {
            std::cerr << "Error: Failed to load necessary textures." << std::endl;
            return 2;
        }
        return 0;
}

void updateWithTimeInterval(double t) {
    //std::cout << "Elapsed time: " << t << std::endl;
    pand2::Position diff = redBall->position - oldpos;
    if (diff.length() > ajx::epsilon) {

        // can use this code to test if position changes.
        // was used for testing. commented to unclutter iostream

        //std::cout << "old position: " << oldpos.x() << " " << oldpos.y() << std::endl;
        //std::cout << "new position: " << redBall->position.x() << " " << redBall->position.y() << std::endl;
    }
    oldpos = redBall->position;

}

int main (int argc, char **argv) {
    try {

        std::cout.precision(17);

        SDL sdl(SDL_INIT_VIDEO|SDL_INIT_TIMER);
        LTexture textures[TEXTURESUM];

        // set up SDL and check if there are issues!
        int returnCode;
        if ((returnCode = setUpSDL(sdl, textures))) {
            return returnCode;
        }

        // Lets set up our physics!
        pand2::Engine e(SCREEN_WIDTH, SCREEN_HEIGHT);
        e.registerUpdateLoop(updateWithTimeInterval);
        e.setGravity(pand2::ForceMake(0.0,-0.0098));

        //std::vector<pand2::SpritePtr> sprites;
        redBall = std::make_shared<pand2::Sprite>();
        redBall->position = pand2::PositionMake(100,100);
        redBall->physicsBody = pand2::PhysicsBody::BodyWithCircleOfRadius(50);
        redBall->dynamic = true;
        redBall->physicsBody.mass = 20.0;
        e.addSprite(redBall);

        e.start();

        // after setting up the physics loop, lets run the event loop to see if the user enters any information
        runEventLoop(sdl, textures);

        // if we get here, the user wanted to quit!
        e.pause(); // lets kill the thread, in case we want to start doing something afterwards

        return 0;
    } catch (const InitError &err) {
        std::cerr << "Error while initializing SDL in stage " << err.stage() << ": " << err.what() << std::endl;
    }

    return 1;
}
