#include "InitSDL.h"

InitError::InitError(): exception(), msg(SDL_GetError()) {}
InitError::InitError(const std::string &m): exception(), msg(m) {}
InitError::~InitError() throw() {}
void InitError::setStage(const std::string &stage) { this->failure_stage = stage; }
const char *InitError::what() const throw() { return msg.c_str(); }
const char *InitError::stage() const throw() { return failure_stage.c_str(); }

SDL::SDL(Uint32 flags) throw(InitError) {
    this->aRenderer = NULL;
    this->aWindow = NULL;
    if (SDL_Init(flags) < 0) {
        InitError e;
        e.setStage("SDL Initialization");
        throw e;
    }
}

void SDL::InitPNG(Uint32 flags) throw(InitError) {
    if (!(IMG_Init(flags) & flags)) {
        InitError e(IMG_GetError());
        e.setStage("PNG Initialization");
        throw e;
    }
}

void SDL::InitWindow(const char *title, int x, int y, int w, int h, Uint32 flags) throw(InitError) {
    this->aWindow = SDL_CreateWindow(title, x, y, w, h, flags);
    if (this->aWindow == NULL) {
        InitError e;
        e.setStage("Window Creation");
        throw e;
    }
}

void SDL::InitRenderer(Uint32 flags, int index) throw(InitError) {
    this->aRenderer = SDL_CreateRenderer(this->aWindow, index, flags);
    if (this->aRenderer == NULL) {
        InitError e;
        e.setStage("Renderer Creation");
        throw e;
    }
}

bool SDL::SetRenderScaleQuality(const char *value) {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, value)) {
        return false;
    }
    return true;
}

bool SDL::SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (!SDL_SetRenderDrawColor(this->aRenderer, r, g, b, a)) {
        return true;
    }
    return false;
}

void SDL::rClear() const {
    SDL_RenderClear(this->aRenderer);
}

void SDL::rPresent() const {
    SDL_RenderPresent(this->aRenderer);
}

void SDL::rCopy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest) {
    SDL_RenderCopy(this->aRenderer, texture, src, dest);
}

SDL::~SDL() {
    if (this->aRenderer != NULL) SDL_DestroyRenderer(this->aRenderer);
    if (this->aWindow != NULL) SDL_DestroyWindow(this->aWindow);

    this->aRenderer = NULL;
    this->aWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}
