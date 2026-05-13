#include "Globals.h"
#include "Gamepad.h"
#include "Character.h"
#include "Texture.h"
#include "Ball.h"

#include "SDL3/SDL.h"
#include "box2d/box2d.h"

#include "DebugDraw.h"

#include <iostream>

Texture background;
Ball* ball;
Gamepad* gamepad = nullptr;
Character* character = nullptr;

bool Init()
{
    // SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == false) {
        SDL_Log("Error initializing SDL - SDL error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!SDL_HasGamepad()) {
        SDL_Log("No gamepads connected - SDL error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if (SDL_CreateWindowAndRenderer("Character Controller for SDL3 and Box2Dv3", screenWidth, screenHeight, 0, &Window, &Renderer) == false) {
        SDL_Log("Window could not be created - SDL error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // background
    if (background.loadFromFile("images/background.png") == false) {
        SDL_Log("Unable to load target image\n");
        return EXIT_FAILURE;
    }

    // Gamepad
    int count = 0;
    SDL_JoystickID* ids = SDL_GetGamepads(&count);
    // only use the first gamepad
    SDL_Gamepad* gp = SDL_OpenGamepad(ids[0]);
    std::cout << "Gamepad connected: " << SDL_GetGamepadName(gp) << std::endl;
    gamepad = new Gamepad(gp);

    // Box2D
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.f, 0.f };
    worldId = b2CreateWorld(&worldDef);

    // Character
    character = new Character(b2Vec2_zero);

    // Ball
    ball = new Ball();

    // Walls
    createStatic(b2Vec2{ 0.f , floatInBox2DWorld(screenHeight) + 1.f }, b2Vec2{ 200.f, 1.0f });
    createStatic(b2Vec2{ 0.f, -1.f }, b2Vec2{ 200.f, 1.0f });
    createStatic(b2Vec2{ -1.f, 0.f }, b2Vec2{ 1.f, 200.f });
    createStatic(b2Vec2{ floatInBox2DWorld(screenWidth) + 1.f, 0.f }, b2Vec2{ 1.f, 200.f });

    // Debug Draw
    debugDrawer = b2DefaultDebugDraw();
    debugDrawer.drawShapes = true;
    debugDrawer.drawBounds = true;

    debugDrawer.DrawPolygonFcn = drawPolygon;
    debugDrawer.DrawSolidPolygonFcn = drawSolidPolygon;
    debugDrawer.DrawSolidCircleFcn = drawSolidCircle;

    return EXIT_SUCCESS;
}

void Close()
{
    delete ball;
    delete character;

    b2DestroyWorld(worldId);
    worldId = b2_nullWorldId;

    delete gamepad;

    background.destroy();

    SDL_DestroyRenderer(Renderer);
    Renderer = nullptr;
    SDL_DestroyWindow(Window);
    Window = nullptr;
    SDL_Quit();
}

int main(int argc, char** argv)
{
    if (Init() == EXIT_FAILURE) {
        std::cout << "Error Initializing - exiting" << std::endl;
        return EXIT_FAILURE;
    }

    bool running = true;
    bool debugDraw = false;
    SDL_Event event;

    while (running) {

        // time
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)(now - last) / (double)freq;
        last = now;
        elapsed += deltaTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                break;
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                const bool* keys = SDL_GetKeyboardState(NULL);
                if (event.key.key == SDLK_ESCAPE) running = false;
                if (event.key.key == SDLK_D) debugDraw = !debugDraw;
            }

            gamepad->update(event);
        }

        // update movement 60 times per seconds
        if (elapsed >= timeStep) {
            ball->update();
            character->update(gamepad, ball);

            b2World_Step(worldId, timeStep, 4);

            elapsed = 0.0;
        }

        if (running) {
            SDL_RenderClear(Renderer);

            background.renderAsBackground(screenWidth, screenHeight);
            character->draw();
            ball->draw();

            if (debugDraw)
                b2World_Draw(worldId, &debugDrawer);

            SDL_RenderPresent(Renderer);
        }
    }

    Close();
    
	return EXIT_SUCCESS;
};