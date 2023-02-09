#include "arbiter.h"
#include "shape.h"
#include "body.h"
#include "space.h"

namespace cp
{
	Arbiter::Arbiter(cpArbiter* arb) : arb(arb) { }

	Arbiter::operator cpArbiter*() const { return arb; }

	cpFloat Arbiter::getElasticity() const { return cpArbiterGetRestitution(arb); }
	void Arbiter::setElasticity(cpFloat elasticity) { cpArbiterSetRestitution(arb, elasticity); }

	cpFloat Arbiter::getFriction() const { return cpArbiterGetFriction(arb); }
	void Arbiter::setFriction(cpFloat friction) { cpArbiterSetFriction(arb, friction); }

	cpVect Arbiter::getSurfaceVelocity() const { return cpArbiterGetSurfaceVelocity(arb); }
	void Arbiter::setSurfaceVelocity(cpVect sv) { cpArbiterSetSurfaceVelocity(arb, sv); }

	int Arbiter::getCount() const { return cpArbiterGetCount(arb); }
	cpVect Arbiter::getNormal() const { return cpArbiterGetNormal(arb); }
	cpVect Arbiter::getPointA(int index) const { return cpArbiterGetPointA(arb, index); }
	cpVect Arbiter::getPointB(int index) const { return cpArbiterGetPointB(arb, index); }
	cpFloat Arbiter::getDepth(int index) const { return cpArbiterGetDepth(arb, index); }

	bool Arbiter::isFirstContact() const { return cpArbiterIsFirstContact(arb); }
	bool Arbiter::isRemoval() const { return cpArbiterIsRemoval(arb); }

	Shape* Arbiter::getShapeA() const
	{
		cpShape* a;
		cpShape* b;
		cpArbiterGetShapes(arb, &a, &b);
		return reinterpret_cast<Shape*>(cpShapeGetUserData(a));
	}

	Shape* Arbiter::getShapeB() const
	{
		cpShape* a;
		cpShape* b;
		cpArbiterGetShapes(arb, &a, &b);
		return reinterpret_cast<Shape*>(cpShapeGetUserData(b));
	}

	Body* Arbiter::getBodyA() const
	{
		cpBody* a;
		cpBody* b;
		cpArbiterGetBodies(arb, &a, &b);
		return reinterpret_cast<Body*>(cpBodyGetUserData(a));
	}

	Body* Arbiter::getBodyB() const
	{
		cpBody* a;
		cpBody* b;
		cpArbiterGetBodies(arb, &a, &b);
		return reinterpret_cast<Body*>(cpBodyGetUserData(b));
	}

	cpContactPointSet Arbiter::getContactPoints() const { return cpArbiterGetContactPointSet(arb); }
	void Arbiter::setContactPoints(cpContactPointSet* contactPoints) { cpArbiterSetContactPointSet(arb, contactPoints); }

	cpVect Arbiter::getTotalImpulse() const { return cpArbiterTotalImpulse(arb); }

	cpFloat Arbiter::getTotalKineticEnergy() const { return cpArbiterTotalKE(arb); }

	bool Arbiter::callWildcardBeginA(Space* space) { return cpArbiterCallWildcardBeginA(arb, *space); }
	bool Arbiter::callWildcardBeginB(Space* space) { return cpArbiterCallWildcardBeginB(arb, *space); }
	bool Arbiter::callWildcardPreSolveA(Space* space) { return cpArbiterCallWildcardPreSolveA(arb, *space); }
	bool Arbiter::callWildcardPreSolveB(Space* space) { return cpArbiterCallWildcardPreSolveB(arb, *space); }
	void Arbiter::callWildcardPostSolveA(Space* space) { cpArbiterCallWildcardPostSolveA(arb, *space); }
	void Arbiter::callWildcardPostSolveB(Space* space) { cpArbiterCallWildcardPostSolveB(arb, *space); }
	void Arbiter::callWildcardSeparateA(Space* space) { cpArbiterCallWildcardSeparateA(arb, *space); }
	void Arbiter::callWildCardSeparateB(Space* space) { cpArbiterCallWildcardSeparateB(arb, *space); }
}