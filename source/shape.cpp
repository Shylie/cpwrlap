#include "shape.h"
#include "body.h"

namespace cp
{
	Shape::Shape(cpShape* shape) : shape(shape), userData(nullptr)
	{
		cpShapeSetUserData(shape, this);
	}

	Shape::operator cpShape*() const { return shape; }

	Body* Shape::getBody() const
	{
		cpBody* body = cpShapeGetBody(shape);
		return static_cast<Body*>(cpBodyGetUserData(body));
	}

	bool Shape::isSensor() const { return cpShapeGetSensor(shape); }
	void Shape::setSensor(bool sensor) { cpShapeSetSensor(shape, sensor); }

	cpFloat Shape::getElasticity() const { return cpShapeGetElasticity(shape); }
	void Shape::setElasticity(cpFloat elasticity) { cpShapeSetElasticity(shape, elasticity); }

	cpFloat Shape::getFriction() const { return cpShapeGetFriction(shape); }
	void Shape::setFriction(cpFloat friction) { cpShapeSetFriction(shape, friction); }

	cpVect Shape::getSurfaceVelocity() const { return cpShapeGetSurfaceVelocity(shape); }
	void Shape::setSurfaceVelocity(cpVect surfaceVelocity) { cpShapeSetSurfaceVelocity(shape, surfaceVelocity); }

	cpCollisionType Shape::getCollisionType() const { return cpShapeGetCollisionType(shape); }
	void Shape::setCollisionType(cpCollisionType collisionType) { cpShapeSetCollisionType(shape, collisionType); }

	cpGroup Shape::getGroup() const { return cpShapeGetFilter(shape).group; }
	void Shape::setGroup(cpGroup group)
	{
		cpShapeFilter filter = cpShapeGetFilter(shape);
		filter.group = group;
		cpShapeSetFilter(shape, filter);
	}

	cpBitmask Shape::getCategories() const { return cpShapeGetFilter(shape).categories; }
	void Shape::setCategories(cpBitmask categories)
	{
		cpShapeFilter filter = cpShapeGetFilter(shape);
		filter.categories = categories;
		cpShapeSetFilter(shape, filter);
	}

	cpBitmask Shape::getMask() const { return cpShapeGetFilter(shape).mask; }
	void Shape::setMask(cpBitmask mask)
	{
		cpShapeFilter filter = cpShapeGetFilter(shape);
		filter.mask = mask;
		cpShapeSetFilter(shape, filter);
	}

	void* Shape::getUserData() const { return userData; }
	void Shape::setUserData(void* data) { userData = data; }
}
