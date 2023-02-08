#include "body.h"
#include "shape.h"
#include "constraint.h"

static void RemoveBodyShape(cpBody* body, cpShape* shape, void* _space)
{
	cpSpace* space = static_cast<cpSpace*>(_space);

	delete static_cast<cp::Shape*>(cpShapeGetUserData(shape));
	cpSpaceRemoveShape(space, shape);
	cpShapeFree(shape);
}

static void RemoveBodyConstraint(cpBody* body, cpConstraint* constraint, void* _space)
{
	cpSpace* space = static_cast<cpSpace*>(_space);

	delete static_cast<cp::Constraint*>(cpConstraintGetUserData(constraint));
	cpSpaceRemoveConstraint(space, constraint);
	cpConstraintFree(constraint);
}

static void RemoveBodyWrap(cpSpace* space, void* _body, void*)
{
	cpBody* body = static_cast<cpBody*>(_body);
	cpBodyEachShape(body, &RemoveBodyShape, space);
	cpBodyEachConstraint(body, &RemoveBodyConstraint, space);

	delete static_cast<cp::Body*>(cpBodyGetUserData(body));
	cpSpaceRemoveBody(space, body);
	cpBodyFree(body);
}

namespace cp
{
	Body::Body(cpFloat mass, cpFloat moment) : body(cpBodyNew(mass, moment)), userData(nullptr)
	{
		cpBodySetUserData(body, this);
	}

	Body::Body(cpBody* body) : body(body), userData(nullptr)
	{
		cpBodySetUserData(body, this);
	}

	Body::operator cpBody*() const { return body; }

	cpBodyType Body::getType() const { return cpBodyGetType(body); }
	void Body::setType(cpBodyType type) { cpBodySetType(body, type); } 

	cpFloat Body::getMass() const { return cpBodyGetMass(body); }
	void Body::setMass(cpFloat mass) { cpBodySetMass(body, mass); }

	cpFloat Body::getMoment() const { return cpBodyGetMoment(body); }
	void Body::setMoment(cpFloat moment) { cpBodySetMoment(body, moment); }

	cpVect Body::getPosition() const { return cpBodyGetPosition(body); }
	void Body::setPosition(cpVect position)
	{
		cpBodySetPosition(body, position);
		cpSpace* space = cpBodyGetSpace(body);
		if (space) { cpSpaceReindexShapesForBody(space, body); }
	}

	cpVect Body::getCenterOfGravity() const { return cpBodyGetCenterOfGravity(body); }
	void Body::setCenterOfGravity(cpVect cog) { cpBodySetCenterOfGravity(body, cog); }

	cpVect Body::getVelocity() const { return cpBodyGetVelocity(body); }
	void Body::setVelocity(cpVect velocity) { cpBodySetVelocity(body, velocity); }

	cpVect Body::getForce() const { return cpBodyGetForce(body); }
	void Body::setForce(cpVect force) { cpBodySetForce(body, force); }

	cpFloat Body::getAngle() const { return cpBodyGetAngle(body); }
	void Body::setAngle(cpFloat angle)
	{
		cpBodySetAngle(body, angle);
		cpSpace* space = cpBodyGetSpace(body);
		if (space) { cpSpaceReindexShapesForBody(space, body); }
	}

	cpFloat Body::getAngularVelocity() const { return cpBodyGetAngularVelocity(body); }
	void Body::setAngularVelocity(cpFloat angularVelocity) { cpBodySetAngularVelocity(body, angularVelocity); }

	cpFloat Body::getTorque() const { return cpBodyGetTorque(body); }
	void Body::setTorque(cpFloat torque) { cpBodySetTorque(body, torque); }

	cpVect Body::getRotation() const { return cpBodyGetRotation(body); }

	void Body::applyForce(cpVect force) { cpBodyApplyForceAtWorldPoint(body, force, cpBodyGetPosition(body)); }
	void Body::applyImpulse(cpVect impulse) { cpBodyApplyImpulseAtWorldPoint(body, impulse, cpBodyGetPosition(body)); }

	void Body::applyForceWorld(cpVect force, cpVect point) { cpBodyApplyForceAtWorldPoint(body, force, point); }
	void Body::applyForceLocal(cpVect force, cpVect point) { cpBodyApplyForceAtLocalPoint(body, force, point); }
	void Body::applyImpulseWorld(cpVect impulse, cpVect point) { cpBodyApplyImpulseAtWorldPoint(body, impulse, point); }
	void Body::applyImpulseLocal(cpVect impulse, cpVect point) { cpBodyApplyImpulseAtLocalPoint(body, impulse, point); }

	void* Body::getUserData() const { return userData; }
	void Body::setUserData(void* data) { userData = data; }

	void Body::remove()
	{
		cpSpace* space = cpBodyGetSpace(body);
		if (cpSpaceIsLocked(space))
		{
			cpSpaceAddPostStepCallback(space, &RemoveBodyWrap, body, nullptr);
		}
		else
		{
			RemoveBodyWrap(space, body, nullptr);
		}
	}
}