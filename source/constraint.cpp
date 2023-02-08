#include "constraint.h"
#include "body.h"

namespace cp
{
	Constraint::Constraint(cpConstraint* constraint) : constraint(constraint), userData(nullptr)
	{
		cpConstraintSetUserData(constraint, this);
	}

	Constraint::operator cpConstraint*() const { return constraint; }

	Body* Constraint::getBodyA() const { return static_cast<Body*>(cpBodyGetUserData(cpConstraintGetBodyA(constraint))); }
	Body* Constraint::getBodyB() const { return static_cast<Body*>(cpBodyGetUserData(cpConstraintGetBodyB(constraint))); }

	cpFloat Constraint::getMaxForce() const { return cpConstraintGetMaxForce(constraint); }
	void Constraint::setMaxForce(cpFloat maxForce) { cpConstraintSetMaxForce(constraint, maxForce); }

	cpFloat Constraint::getErrorBias() const { return cpConstraintGetErrorBias(constraint); }
	void Constraint::setErrorBias(cpFloat errorBias) { cpConstraintSetErrorBias(constraint, errorBias); }

	cpFloat Constraint::getMaxBias() const { return cpConstraintGetMaxBias(constraint); }
	void Constraint::setMaxBias(cpFloat maxBias) { cpConstraintSetMaxBias(constraint, maxBias); }

	bool Constraint::shouldCollideBodies() const { return cpConstraintGetCollideBodies(constraint); }
	void Constraint::setShouldCollideBodies(bool collideBodies) { cpConstraintSetCollideBodies(constraint, collideBodies); }

	void* Constraint::getUserData() const { return userData; }
	void Constraint::setUserData(void* data) { userData = data; }

	cpFloat Constraint::getImpulse() { return cpConstraintGetImpulse(constraint); }
}
