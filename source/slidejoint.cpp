#include "slidejoint.h"
#include "body.h"

namespace cp
{
	SlideJoint::SlideJoint(Body* a, Body* b, cpVect anchorA, cpVect anchorB, cpFloat min, cpFloat max) :
		Constraint(cpSlideJointNew(*a, *b, anchorA, anchorB, min, max))
	{ }

	SlideJoint::SlideJoint(Body* a, Body* b, cpFloat min, cpFloat max) :
		SlideJoint(a, b, cpvzero, cpvzero, min, max)
	{ }

	cpVect SlideJoint::getAnchorALocal() const { return cpSlideJointGetAnchorA(constraint); }
	cpVect SlideJoint::getAnchorBLocal() const { return cpSlideJointGetAnchorB(constraint); }

	void SlideJoint::setAnchorALocal(cpVect anchorA) { cpSlideJointSetAnchorA(constraint, anchorA); }
	void SlideJoint::setAnchorBLocal(cpVect anchorB) { cpSlideJointSetAnchorB(constraint, anchorB); }

	cpVect SlideJoint::getAnchorAWorld() const { return cpBodyLocalToWorld(*getBodyA(), getAnchorALocal()); }
	cpVect SlideJoint::getAnchorBWorld() const { return cpBodyLocalToWorld(*getBodyB(), getAnchorBLocal()); }

	void SlideJoint::setAnchorAWorld(cpVect anchorA) { setAnchorALocal(cpBodyWorldToLocal(*getBodyA(), anchorA)); }
	void SlideJoint::setAnchorBWorld(cpVect anchorB) { setAnchorBLocal(cpBodyWorldToLocal(*getBodyB(), anchorB)); }

	cpFloat SlideJoint::getMin() const { return cpSlideJointGetMin(constraint); }
	void SlideJoint::setMin(cpFloat min) { cpSlideJointSetMin(constraint, min); }

	cpFloat SlideJoint::getMax() const { return cpSlideJointGetMax(constraint); }
	void SlideJoint::setMax(cpFloat max) { cpSlideJointSetMax(constraint, max); }

	void SlideJoint::draw(Color color) const
	{
		const cpVect anchorA = getAnchorAWorld();
		const cpVect anchorB = getAnchorBWorld();

		const cpFloat min = getMin();
		const cpFloat max = getMax();
		const cpFloat actual = cpvdist(anchorA, anchorB);
		const cpFloat t = (actual - min) / (max - min);
		
		const cpVect normTowardsA = cpvmult(cpvsub(anchorA, anchorB), 1 / actual);
		const cpVect perp = cpvperp(normTowardsA);

		const cpVect mid = cpvlerp(anchorA, anchorB, 0.5);
		const cpVect midA = cpvlerp(mid, anchorA, 0.33);
		const cpVect midB = cpvlerp(mid, anchorB, 0.33);

		const cpVect offsetA = cpvlerp(mid, midA, t);
		const cpVect offsetB = cpvlerp(mid, midB, t);

		const cpVect perp5 = cpvmult(perp, 5);

		const cpVect boxALeft = cpvadd(offsetA, perp5);
		const cpVect boxARight = cpvsub(offsetA, perp5);

		const cpVect boxBLeft = cpvadd(offsetB, perp5);
		const cpVect boxBRight = cpvsub(offsetB, perp5);

		DrawLineEx(
			Vector2{ static_cast<float>(anchorA.x), static_cast<float>(anchorA.y) },
			Vector2{ static_cast<float>(offsetA.x), static_cast<float>(offsetA.y) },
			1, color
		);

		DrawLineEx(
			Vector2{ static_cast<float>(anchorB.x), static_cast<float>(anchorB.y) },
			Vector2{ static_cast<float>(offsetB.x), static_cast<float>(offsetB.y) },
			1, color
		);

		DrawLineEx(
			Vector2{ static_cast<float>(boxALeft.x), static_cast<float>(boxALeft.y) },
			Vector2{ static_cast<float>(boxARight.x), static_cast<float>(boxARight.y) },
			1, color
		);

		DrawLineEx(
			Vector2{ static_cast<float>(boxBLeft.x), static_cast<float>(boxBLeft.y) },
			Vector2{ static_cast<float>(boxBRight.x), static_cast<float>(boxBRight.y) },
			1, color
		);

		DrawLineEx(
			Vector2{ static_cast<float>(boxALeft.x), static_cast<float>(boxALeft.y) },
			Vector2{ static_cast<float>(boxBLeft.x), static_cast<float>(boxBLeft.y) },
			1, color
		);

		DrawLineEx(
			Vector2{ static_cast<float>(boxARight.x), static_cast<float>(boxARight.y) },
			Vector2{ static_cast<float>(boxBRight.x), static_cast<float>(boxBRight.y) },
			1, color
		);
	}
}