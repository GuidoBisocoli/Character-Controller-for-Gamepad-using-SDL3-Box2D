#include "Ball.h"

#include "Globals.h"

#include "box2d/box2d.h"

Ball::Ball()
	: bodyId(b2_nullBodyId)
{
	// SDL
	if (texture.loadFromFile("images/ball.png") == false) {
		SDL_Log("Unable to load ball image\n");
		return;
	}

	// Box2D
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = SDL_FPoint_to_b2Vec({ 10.f, 10.f });
	bodyDef.linearDamping = 0.7f;

	bodyId = b2CreateBody(worldId, &bodyDef);

	b2Circle circleShape;
	circleShape.center = b2Vec2_zero;
	circleShape.radius = RADIUS;

	b2ShapeDef circleDef = b2DefaultShapeDef();
	circleDef.material.restitution = 0.6f;
	circleDef.density = 75.f;

	b2ShapeId shapeId = b2CreateCircleShape(bodyId, &circleDef, &circleShape);
}

Ball::~Ball()
{
}

void Ball::kick(kickType t, b2Vec2 direction)
{
	if (cooldownTimer > 0.f) return;

	float force = 0.f;

	switch (t)
	{
		case Ball::tap: force = 40.f; break;
		case Ball::soft: force = 70.f; break;
		case Ball::strong: force = 120.f; break;
	}

	b2Body_ApplyLinearImpulseToCenter(bodyId, force * direction, true);

	cooldownTimer = 1.f;
}

b2Vec2 Ball::getPosition()
{
	return b2Body_GetPosition(bodyId);
}

void Ball::update()
{
	if (cooldownTimer > 0.f)
		cooldownTimer -= timeStep;
}

void Ball::draw()
{
	float diameterPxels = floatToSDL(RADIUS * 2.f);

	SDL_FPoint pos = b2Vec_to_SDL_FPoint(b2Body_GetPosition(bodyId));
	SDL_FRect posOnScreen {
		pos.x - (diameterPxels / 2.0f),
		pos.y - (diameterPxels / 2.0f),
		diameterPxels,
		diameterPxels
	};

	texture.render(texture.getFRect(), posOnScreen, 0.f);
}