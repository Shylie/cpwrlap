#include <cpwrlap.h>
#include <raylib.h>
#include <chipmunk.h>

int main()
{
	cp::Space space;
	space.setGravity(cpv(0, 10));

	cp::Shape* ground = space.add(new cp::SegmentShape(space.getStaticBody(), cpv(-10, 20), cpv(640, 360), 0));
	ground->setFriction(1);

	constexpr cpFloat mass = 1;
	constexpr cpFloat radius = 5;

	cp::Body* circleBody = space.add(new cp::Body(mass, cpMomentForCircle(mass, radius, 0, cpvzero)));
	circleBody->setPosition(cpv(5, 0));
	cp::Shape* circleShape = space.add(new cp::CircleShape(circleBody, radius, cpvzero));
	circleShape->setFriction(1);

	cp::Body* boxBody = space.add(new cp::Body(mass, cpMomentForBox(mass, radius * 2.0, radius * 2)));
	boxBody->setPosition(cpv(5, 40));
	cp::Shape* boxShape = space.add(new cp::PolygonShape(boxBody, radius * 2, radius * 2));
	boxShape->setFriction(1);

	space.add(new cp::PinJoint(circleBody, boxBody, cpvzero, cpvzero));

	Camera2D cam;
	cam.offset = Vector2{ 320, 180 };
	cam.zoom = 2.0;
	cam.rotation = 0.0;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
	InitWindow(640, 360, "example");

	while (!WindowShouldClose())
	{
		space.step(1.0 / 60.0);

		cpVect pos = circleBody->getPosition();
		cam.target = Vector2{ pos.x, pos.y };

		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode2D(cam);
		space.draw(GREEN, RED);
		EndMode2D();

		EndDrawing();
	}

	CloseWindow();
}
