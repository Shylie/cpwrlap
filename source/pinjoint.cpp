#include "pinjoint.h"
#include "body.h"

namespace cp
{
	PinJoint::PinJoint(Body* a, Body* b, cpVect anchorA, cpVect anchorB, cpFloat dist) : Constraint(cpPinJointNew(*a, *b, anchorA, anchorB))
	{
		setDistance(dist);
	}
	PinJoint::PinJoint(Body* a, Body* b, cpVect anchorA, cpVect anchorB) : Constraint(cpPinJointNew(*a, *b, anchorA, anchorB)) { }
	PinJoint::PinJoint(Body* a, Body* b, cpFloat dist) : PinJoint(a, b, cpvzero, cpvzero, dist) { }

	cpVect PinJoint::getAnchorALocal() const { return cpPinJointGetAnchorA(constraint); }
	cpVect PinJoint::getAnchorBLocal() const { return cpPinJointGetAnchorB(constraint); }

	void PinJoint::setAnchorALocal(cpVect anchorA) { cpPinJointSetAnchorA(constraint, anchorA); }
	void PinJoint::setAnchorBLocal(cpVect anchorB) { cpPinJointSetAnchorB(constraint, anchorB); }

	cpVect PinJoint::getAnchorAWorld() const { return cpBodyLocalToWorld(*getBodyA(), getAnchorALocal()); }
	cpVect PinJoint::getAnchorBWorld() const { return cpBodyLocalToWorld(*getBodyB(), getAnchorBLocal()); }

	void PinJoint::setAnchorAWorld(cpVect anchorA) { setAnchorALocal(cpBodyWorldToLocal(*getBodyA(), anchorA)); }
	void PinJoint::setAnchorBWorld(cpVect anchorB) { setAnchorBLocal(cpBodyWorldToLocal(*getBodyB(), anchorB)); }

	cpFloat PinJoint::getDistance() const { return cpPinJointGetDist(constraint); }
	void PinJoint::setDistance(cpFloat dist) { cpPinJointSetDist(constraint, dist); }

	void PinJoint::draw(Color color) const
	{
		const cpVect anchorA = getAnchorAWorld();
		const cpVect anchorB = getAnchorBWorld();

		DrawLineEx(
			Vector2{ static_cast<float>(anchorA.x), static_cast<float>(anchorA.y) },
			Vector2{ static_cast<float>(anchorB.x), static_cast<float>(anchorB.y) },
			1, color
		);
	}
}
