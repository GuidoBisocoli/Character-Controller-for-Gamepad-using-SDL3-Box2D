#pragma once

#include <box2d/box2d.h>
#include "Globals.h"

b2DebugDraw debugDrawer;     // For drawing colliders during debugging

void drawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context)
{
    // 2. Extract RGBA components from b2HexColor (0xRRGGBBAA)
    uint8_t r = (uint8_t)((color >> 24) & 0xFF);
    uint8_t g = (uint8_t)((color >> 16) & 0xFF);
    uint8_t b = (uint8_t)((color >> 8) & 0xFF);
    uint8_t a = (uint8_t)(color & 0xFF);

    // 3. Set the draw color in SDL3
    SDL_SetRenderDrawColor(Renderer, r, g, b, a);

    // 4. Draw lines between sequential vertices
    for (int i = 0; i < vertexCount; ++i)
    {
        const b2Vec2& v1 = vertices[i] * SCALE;
        // Wrap around to the first vertex for the final segment
        const b2Vec2& v2 = vertices[(i + 1) % vertexCount] * SCALE;

        // Using SDL_RenderLine for subpixel precision
        SDL_RenderLine(Renderer, v1.x, v1.y, v2.x, v2.y);
    }
}

void drawSolidPolygon(b2Transform transform, const b2Vec2* vertices,
    int vertexCount, float radius, b2HexColor color, void* context)
{
    // Get the pixel format
    SDL_Surface* surface = SDL_GetWindowSurface(Window);
    const SDL_PixelFormatDetails* format = SDL_GetPixelFormatDetails(surface->format);
    // Extract RGB
    Uint8 r, g, b;
    SDL_GetRGB(color, format, NULL, &r, &g, &b);
    // Draw a collider rectangle with lines
    SDL_SetRenderDrawColor(Renderer, r, g, b, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < vertexCount; ++i) {
        int next_index = (i + 1 == vertexCount) ? 0 : i + 1;
        b2Vec2 p0 = b2TransformPoint(transform, vertices[i]);
        b2Vec2 p1 = b2TransformPoint(transform, vertices[next_index]);
        float x0 = p0.x * SCALE;
        float y0 = p0.y * SCALE;
        float x1 = p1.x * SCALE;
        float y1 = p1.y * SCALE;
        SDL_RenderLine(Renderer, x0, y0, x1, y1);
    }
}

void drawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context)
{
    // Convertir color Hex de Box2D 3.0 a RGBA de SDL3
    // Box2D 3.0 usa b2HexColor (ej: 0xFFFF00)
    uint8_t r = (uint8_t)((color >> 16) & 0xFF);
    uint8_t g = (uint8_t)((color >> 8) & 0xFF);
    uint8_t b = (uint8_t)(color & 0xFF);

    // Dibujar el círculo (aproximación por segmentos)
    const int segments = 24;
    const float angleStep = 2.0f * SDL_PI_F / segments;

    // Convertir la posición de Box2D a coordenadas de pantalla
    float centerX = transform.p.x * SCALE;
    float centerY = transform.p.y * SCALE;

    for (int i = 0; i < segments; ++i) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        // Nota: Aquí deberías aplicar tu escala de Mtrs -> Píxeles
        float x1 = centerX + radius * SDL_cosf(angle1) * SCALE;
        float y1 = centerY + radius * SDL_sinf(angle1) * SCALE;
        float x2 = centerX + radius * SDL_cosf(angle2) * SCALE;
        float y2 = centerY + radius * SDL_sinf(angle2) * SCALE;

        SDL_RenderLine(Renderer, x1, y1, x2, y2);
    }
}