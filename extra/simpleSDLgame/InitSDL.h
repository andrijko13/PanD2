#ifndef AS_SDL
#define AS_SDL
#include <exception>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define NUMBER_OF_INIT_STAGES 4

class InitError: public std::exception {
    public:
        // Methods
        InitError();
        InitError(const std::string&);
        virtual ~InitError() throw();

        virtual void setStage(const std::string &stage);
        virtual const char *what() const throw();
        virtual const char *stage() const throw();

        // iVars

    private:
        std::string msg;
        std::string failure_stage;
};

class SDL {
    public:
        SDL(Uint32 flags = 0) throw(InitError);
        virtual ~SDL();

        // Methods
        void InitWindow(const char *title, int x, int y, int w, int h, Uint32 flags) throw(InitError);
        void InitPNG(Uint32 flags) throw(InitError);
        void InitRenderer(Uint32 flags, int index = -1) throw(InitError);
        bool SetRenderScaleQuality(const char * value);
        bool SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        void rClear() const;
        void rCopy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest);
        void rPresent() const;

        // iVars
        SDL_Window   *aWindow;          // Window we will be rendering to
        SDL_Renderer *aRenderer;        // Window renderer
    private:

};

#endif
