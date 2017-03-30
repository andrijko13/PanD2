#ifndef LTEXTURE_SDL
#define LTEXTURE_SDL

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class LTexture {
    public:
        LTexture();
        LTexture(SDL_Renderer *);
        ~LTexture();
        bool loadFromFile(const std::string &path);
        void free();
        void render(int x, int y, SDL_Rect *clip = NULL);
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture *mTexture;
        SDL_Renderer *mRenderer;

        int mWidth;
        int mHeight;
};

#endif
