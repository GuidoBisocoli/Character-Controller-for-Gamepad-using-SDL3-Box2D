#include "Globals.h"

#include "box2d/box2d.h"

// constants
const int screenWidth = 1600;
const int screenHeight = 900;
const float timeStep = 1.0 / 60.0;
const unsigned int SCALE = 64.f; // 1m = 64px;

// time & fps
Uint64 freq = SDL_GetPerformanceFrequency();
Uint64 last = SDL_GetPerformanceCounter();
Uint64 now = 0;
double deltaTime = 0.0;
double elapsed = 0.0;

// box2d
b2WorldId worldId = {};

// SDL
SDL_Window* Window{ nullptr };
SDL_Renderer* Renderer{ nullptr };

// helpers
float floatInBox2DWorld(const float f)
{
	return f / SCALE;
}

float floatToSDL(const float f)
{
	return f * SCALE;
}

b2Vec2 SDL_FPoint_to_b2Vec(SDL_FPoint v)
{
	return b2Vec2{ SCALE / v.x, SCALE / v.y };
}


SDL_FPoint b2Vec_to_SDL_FPoint(b2Vec2 v) {
	return SDL_FPoint{ SCALE * v.x, SCALE * v.y };
}

void createStatic(b2Vec2 pos, b2Vec2 halfSize)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_staticBody;
	bodyDef.position = pos;

	b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

	b2Polygon box = b2MakeBox(halfSize.x, halfSize.y);
	b2ShapeDef shapeDef = b2DefaultShapeDef();

	bodyId = b2CreateBody(worldId, &bodyDef);

	b2CreatePolygonShape(bodyId, &shapeDef, &box);
}

