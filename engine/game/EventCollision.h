#pragma once
#include "../Event.h"
#include "Object.h"
#include "../Vector.h"

namespace df {
	const std::string COLLISION_EVENT = "collision";

	class EventCollision : public Event {
	private:
		Vector m_pos; //position of collision
		Object* obj1 = NULL; //moving causing collision
		Object* obj2 = NULL; //collided with
	public:
		/// <summary>
		/// Create default collsion at pos 0, 0 with null objects
		/// </summary>
		EventCollision();

		/// <summary>
		/// Create collision of obj1 moving into obj2 at the given pos
		/// </summary>
		EventCollision(Object* obj1, Object* obj2, Vector pos);

		/// <summary>
		/// Set position collison.
		/// </summary>
		void setPos(Vector pos);

		/// <summary>
		/// Get position collison.
		/// </summary>
		Vector getPos() const;

		/// <summary>
		/// Set object pointer of object moving into collison.
		/// </summary>
		void setObject1(Object* obj1);

		/// <summary>
		/// Get object pointer of object moving into collison.
		/// </summary>
		Object* getObject1() const;

		/// <summary>
		/// Set object pointer of object being collided into.
		/// </summary>
		void setObject2(Object* obj2);

		/// <summary>
		/// Get object pointer of object being collided into.
		/// </summary>
		Object* getObject2() const;
	};
}