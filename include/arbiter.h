#ifndef CPWRLAP_ARBITER_H
#define CPWRLAP_ARBITER_H

#include <chipmunk.h>

namespace cp
{
	class Shape;
	class Body;
	class Space;

	class Arbiter
	{
	private:
		cpArbiter* arb;

	public:
		Arbiter(cpArbiter*);

		operator cpArbiter*() const;

		cpFloat getElasticity() const;
		void setElasticity(cpFloat);

		cpFloat getFriction() const;
		void setFriction(cpFloat);

		cpVect getSurfaceVelocity() const;
		void setSurfaceVelocity(cpVect);

		cpVect getNormal() const;
		int getCount() const;
		cpVect getPointA(int) const;
		cpVect getPointB(int) const;
		cpFloat getDepth(int) const;

		bool isFirstContact() const;
		bool isRemoval() const;

		Shape* getShapeA() const;
		Shape* getShapeB() const;
		Body* getBodyA() const;
		Body* getBodyB() const;

		cpContactPointSet getContactPoints() const;
		void setContactPoints(cpContactPointSet*);

		cpVect getTotalImpulse() const;

		cpFloat getTotalKineticEnergy() const;

		bool callWildcardBeginA(Space*);
		bool callWildcardBeginB(Space*);
		bool callWildcardPreSolveA(Space*);
		bool callWildcardPreSolveB(Space*);
		void callWildcardPostSolveA(Space*);
		void callWildcardPostSolveB(Space*);
		void callWildcardSeparateA(Space*);
		void callWildCardSeparateB(Space*);
	};
}

#endif//CPWRLAP_ARBITER_H
