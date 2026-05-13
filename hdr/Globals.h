#pragma once

#include <SDL3/SDL.h>
#include "box2d/id.h"

struct b2Vec2;

// constants
extern const int screenWidth;
extern const int screenHeight;
extern const float timeStep;
extern const unsigned int SCALE;

// time & fps
extern Uint64 freq;
extern Uint64 last;
extern Uint64 now;
extern double deltaTime;
extern double elapsed;

// box2d
extern b2WorldId worldId;

// SDL
extern SDL_Window* Window;
extern SDL_Renderer* Renderer;

// helpers
extern float floatInBox2DWorld(const float f);
extern float floatToSDL(const float f);
extern b2Vec2 SDL_FPoint_to_b2Vec(SDL_FPoint v);
extern SDL_FPoint b2Vec_to_SDL_FPoint(b2Vec2 v);
extern void createStatic(b2Vec2 pos, b2Vec2 halfSize);


