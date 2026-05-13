#pragma once

#include <SDL3/SDL.h>
#include <string>

class Texture
{
public:
    Texture();
    ~Texture();

    bool loadFromFile(std::string path);

    void destroy();

    void setColor(SDL_Color c);
    void setAlpha(Uint8 alpha);

    void renderAsBackground(float xOnScreen, float yOnScreen);
    void render(const SDL_FRect srcrect, const SDL_FRect dstrect, double angle);

    SDL_FRect getFRect() const { return SDL_FRect{ 0.f, 0.f, (float)mWidth, (float)mHeight }; }
    SDL_Point getSize() const { return SDL_Point{ mWidth, mHeight }; }
    int getWidth();
    int getHeight();
    bool isLoaded();

    operator SDL_Texture* () { return mTexture; }
private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};