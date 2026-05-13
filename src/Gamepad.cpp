#include "Gamepad.h"

#include "SDL3/SDL.h"

Gamepad::Gamepad(SDL_Gamepad* gp) : sdlGamepad(gp)
{
}

Gamepad::~Gamepad()
{
    SDL_CloseGamepad(sdlGamepad);
}

void Gamepad::update(SDL_Event event)
{
    if (event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN
        || event.type == SDL_EVENT_GAMEPAD_BUTTON_UP) {

        switch (event.gbutton.button) {
        case SDL_GAMEPAD_BUTTON_SOUTH: // A on XInput
            state.a_pressed = event.gbutton.down; break;
        case SDL_GAMEPAD_BUTTON_EAST: // B on XInput
            state.b_pressed = event.gbutton.down; break;
        case SDL_GAMEPAD_BUTTON_WEST: // X on XInput
            state.x_pressed = event.gbutton.down; break;
        case SDL_GAMEPAD_BUTTON_NORTH: // Y on XInput
            state.y_pressed = event.gbutton.down; break;
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
            state.ls_pressed = event.gbutton.down; break;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
            state.rs_pressed = event.gbutton.down; break;
        case SDL_GAMEPAD_BUTTON_BACK:
            state.back_pressed = event.gbutton.down; break;
        case SDL_GAMEPAD_BUTTON_START:
            state.start_pressed = event.gbutton.down; break;
        default:
            break;
        }
    }
    
    else if (event.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {

        if (event.gaxis.axis == SDL_GAMEPAD_AXIS_LEFTX) {
            if (event.gaxis.value > DEADZONE || event.gaxis.value < -DEADZONE)
                state.leftStick_x_axis = event.gaxis.value;
            else 
                state.leftStick_x_axis = 0;
        }
            
        else if (event.gaxis.axis == SDL_GAMEPAD_AXIS_LEFTY) {
            if (event.gaxis.value > DEADZONE || event.gaxis.value < -DEADZONE)
                state.leftStick_y_axis = event.gaxis.value;
            else
                state.leftStick_y_axis = 0;
        }

        if (event.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHTX) {
            if (event.gaxis.value > DEADZONE || event.gaxis.value < -DEADZONE)
                state.rightStick_x_axis = event.gaxis.value;
            else 
                state.rightStick_x_axis = 0;
        }
            
        else if (event.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHTY) {
            if (event.gaxis.value > DEADZONE || event.gaxis.value < -DEADZONE)
                state.rightStick_y_axis = event.gaxis.value;
            else
                state.rightStick_y_axis = 0;
        }

    }
}
