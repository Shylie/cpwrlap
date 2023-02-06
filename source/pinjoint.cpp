#include "pinjoint.h"
#include "body.h"

namespace cp
{
	PinJoint::PinJoint(Body* a, Body* b, cpVect anchorA, cpVect anchorB) : Constraint(cpPinJointNew(*a, *b, anchorA, anchorB)) { }
	PinJoint::PinJoint(Body* a, Body* b, cpFloat dist) : Constraint(cpPinJointNew(*a, *b, cpvzero, cpvzero))
	{
		setDistance(dist);
	}

	cpVect PinJoint::getAnchorALocal() const { return cpPinJointGetAnchorA(constraint); }
	cpVect PinJoint::getAnchorBLocal() const { return cpPinJointGetAnchorB(constraint); }

	void PinJoint::setAnchorALocal(cpVect anchorA) { cpPinJointSetAnchorA(constraint, anchorA); }
	void PinJoint::setAnchorBLocal(cpVect anchorB) { cpPinJointSetAnchorB(constraint, anchorB); }

	cpVect PinJoint::getAnchorAWorld() const { return cpBodyLocalToWorld(*getBodyA(), getAnchorALocal()); }
	cpVect PinJoint::getAnchorBWorld() const { return cpBodyLocalToWorld(*getBodyB(), getAnchorBLocal()); }

	cpFloat PinJoint::getDistance() const { return cpPinJointGetDist(constraint); }
	void PinJoint::setDistance(cpFloat dist) { cpPinJointSetDist(constraint, dist); }

	void PinJoint::draw(Color color) const
	{
		cpVect anchorA = getAnchorAWorld();
		cpVect anchorB = getAnchorBWorld();

		DrawLineEx(
			Vector2{ static_cast<float>(anchorA.x), static_cast<float>(anchorA.y) },
			Vector2{ static_cast<float>(anchorB.x), static_cast<float>(anchorB.y) },
			1, color
		);
	}
}
