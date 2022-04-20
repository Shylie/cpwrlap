#ifndef CPWRLAP_SPACE_H
#define CPWRLAP_SPACE_H

#include <utility>
#include <unordered_map>
#include <vector>

#include <chipmunk.h>
#include <raylib.h>

namespace cp
{
	class Shape;
	class Body;
	class Constraint;
	class Arbiter;

	class Space
	{
	public:
		typedef int (*CollisionBeginFunc)(Arbiter, Space&, void*);
		typedef int (*CollisionPreSolveFunc)(Arbiter, Space&, void*);
		typedef void (*CollisionPostSolveFunc)(Arbiter, Space&, void*);
		typedef void (*CollisionSeparateFunc)(Arbiter, Space&, void*);

	private:
		cpSpace* space;

		Body* staticBody;

		void* data;

		std::vector<Shape*> shapes;
		std::vector<Body*> bodies;
		std::vector<Constraint*> constraints;

		struct CallbackData
		{
			CollisionBeginFunc begin;
			CollisionPreSolveFunc preSolve;
			CollisionPostSolveFunc postSolve;
			CollisionSeparateFunc separate;
			void* data;
		};

		std::unordered_map<cpCollisionHandler*, CallbackData> collisionCallbackData;

		CallbackData& setupCallbackData(cpCollisionHandler*);

		static int collisionBeginFuncHelper(cpArbiter*, cpSpace*, CallbackData*);
		static int collisionPreSolveFuncHelper(cpArbiter*, cpSpace*, CallbackData*);
		static void collisionPostSolveFuncHelper(cpArbiter*, cpSpace*, CallbackData*);
		static void collisionSeparateFuncHelper(cpArbiter*, cpSpace*, CallbackData*);

	public:
		Space();
		~Space();

		Space(const Space&) = delete;
		Space& operator=(const Space&) = delete;

		operator cpSpace*() const;

		void* getUserData() const;
		void setUserData(void*);

		Shape* add(Shape*);
		Body* add(Body*);
		Constraint* add(Constraint*);

		void remove(Shape*);
		void remove(Body*);
		void remove(Constraint*);

		Body* getStaticBody();

		cpVect getGravity() const;
		void setGravity(cpVect);

		void step(cpFloat);
		void draw(Color, Color) const;

		void setCollisionBeginFunc(cpCollisionType, cpCollisionType, CollisionBeginFunc);
		void setCollisionPreSolveFunc(cpCollisionType, cpCollisionType, CollisionPreSolveFunc);
		void setCollisionPostSolveFunc(cpCollisionType, cpCollisionType, CollisionPostSolveFunc);
		void setCollisionSeparateFunc(cpCollisionType, cpCollisionType, CollisionSeparateFunc);
		void setCollisionUserData(cpCollisionType, cpCollisionType, void*);

		void setWildcardCollisionBeginFunc(cpCollisionType, CollisionBeginFunc);
		void setWildcardCollisionPreSolveFunc(cpCollisionType, CollisionPreSolveFunc);
		void setWildcardCollisionPostSolveFunc(cpCollisionType, CollisionPostSolveFunc);
		void setWildcardCollisionSeparateFunc(cpCollisionType, CollisionSeparateFunc);
		void setWildcardCollisionUserData(cpCollisionType, void*);
 
		void setDefaultCollisionBeginFunc(CollisionBeginFunc);
		void setDefaultCollisionPreSolveFunc(CollisionPreSolveFunc);
		void setDefaultCollisionPostSolveFunc(CollisionPostSolveFunc);
		void setDefaultCollisionSeparateFunc(CollisionSeparateFunc);
		void setDefaultCollisionUserData(void*);
	};
}

#endif//CPWRLAP_SPACE_H
