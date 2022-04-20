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
	cp::Shape* circleShape = space.add(new cp::CircleShape(circleBody, radius, cpvzero));
	circleShape->setFriction(1);

	cp::Body* boxBody = space.add(new cp::Body(mass, cpMomentForBox(mass, radius * 2.0, radius * 2)));
	boxBody->setPosition(cpv(40, 0));
	cp::Shape* boxShape = space.add(new cp::PolygonShape(boxBody, radius * 2, radius * 2));
	boxShape->setFriction(1);

	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(640, 360, "example");

	while (!WindowShouldClose())
	{
		space.step(1.0 / 60.0);

		BeginDrawing();
		ClearBackground(BLACK);

		space.draw(GREEN, RED);

		EndDrawing();
	}

	CloseWindow();
}
