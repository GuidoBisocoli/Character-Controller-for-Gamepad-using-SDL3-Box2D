#pragma once

#include <stdint.h>

union SDL_Event;
struct SDL_Gamepad;

class Gamepad
{
public:
	struct State {
		bool a_pressed = false;
		bool b_pressed = false;
		bool x_pressed = false;
		bool y_pressed = false;
		bool ls_pressed = false;
		bool rs_pressed = false;
		bool back_pressed = false;
		bool start_pressed = false;
		int16_t leftStick_x_axis = 0;
		int16_t leftStick_y_axis = 0;
		int16_t rightStick_x_axis = 0;
		int16_t rightStick_y_axis = 0;
	} state;

	Gamepad(SDL_Gamepad* gp);
	~Gamepad();

	void update(SDL_Event event);

private:
	SDL_Gamepad* sdlGamepad;
	const int DEADZONE = 9000;
};