#include "Character.h"

#include "Globals.h"
#include "Gamepad.h"
#include "Ball.h"

#include "box2d/box2d.h"

Character::Character(b2Vec2 position)
	: bodyId(b2_nullBodyId), movement(b2Vec2_zero), angle(0.f)
{
	// SDL
	if (texture.loadFromFile("images/man.png") == false) {
		SDL_Log("Unable to load man image\n");
		return;
	}

	// Box2D
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = position;

	bodyId = b2CreateBody(worldId, &bodyDef);

	b2Circle circleShape;
	circleShape.center = b2Vec2_zero;
	circleShape.radius = RADIUS;

	b2ShapeDef circleDef = b2DefaultShapeDef();
	circleDef.material.restitution = 0.2f;
	circleDef.density = 75.f;

	b2ShapeId shapeId = b2CreateCircleShape(bodyId, &circleDef, &circleShape);
}

Character::~Character()
{
	texture.destroy();
}

#include <iostream>
void Character::update(Gamepad* gp, Ball* b)
{
	// movement
	movement.x = (float)gp->state.leftStick_x_axis / (float)SDL_JOYSTICK_AXIS_MAX;
	movement.y = (float)gp->state.leftStick_y_axis / (float)SDL_JOYSTICK_AXIS_MAX;

	movement *= MAXSPEED * timeStep;

	if (gp->state.rs_pressed)
		movement *= RUN_MULTIPLIER;


	b2Body_SetLinearVelocity(bodyId, movement);

	// actions
	float distSqToBall = b2DistanceSquared(b->getPosition(), b2Body_GetPosition(bodyId)); // no need to calculate the root squared
	if (distSqToBall > 0.6f * 0.6f) return; // to far away from ball

	if (gp->state.a_pressed) {
		b->kick(Ball::kickType::tap, b2Normalize(movement));
	}
	if (gp->state.b_pressed) {
		b->kick(Ball::kickType::strong, b2Normalize(movement));
	}
	if (gp->state.x_pressed) {
		b->kick(Ball::kickType::soft, b2Normalize(movement));
	}
}

void Character::draw()
{
	b2Vec2 b2Pos = b2Body_GetPosition(bodyId);
	SDL_FPoint pos = b2Vec_to_SDL_FPoint(b2Pos);
	SDL_FRect posOnScreen {
		pos.x - texture.getWidth() / 2.f,
		pos.y - texture.getHeight() / 2.f,
		texture.getWidth(),
		texture.getHeight()
	};

	if (movement != b2Vec2_zero)
		calculateAngle(b2Pos, b2Pos + movement);

	texture.render(texture.getFRect(), posOnScreen, angle);
}

#include <cmath>
void Character::calculateAngle(b2Vec2 pos, b2Vec2 target)
{
	float deltaX = (float)(target.x - pos.x);
	float deltaY = (float)(target.y - pos.y);

	float angleRadians = std::atan2(deltaY, deltaX);

	angle = angleRadians * (180.0f / SDL_PI_F);
}
