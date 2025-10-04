#pragma once
#include "../Manager.h"
#include "ObjectList.h"

#define WM df::WorldManager::GetInstance()

namespace df {
	/// <summary>
	/// A class for managing the world and its objects in the game engine.
	/// </summary>
	class WorldManager : public Manager
	{
	private:
		//singleton stuff
		WorldManager();
		WorldManager(WorldManager const& copy);
		void operator=(WorldManager const& assign);

		ObjectList m_updates; //objects to update
		ObjectList m_deletions; //onjects to delete

	public:
		/// <summary>
		/// Destroys the world manager and any other dependencies.
		/// </summary>
		~WorldManager();

		/// <summary>
		/// Get instance of the one and only WorldManager.
		/// </summary>
		/// <returns></returns>
		static WorldManager& GetInstance();

		/// <summary>
		/// Start up WorldManager and required dependencies.
		/// </summary>
		/// <returns>0 if successful.</returns>
		int startUp() override;

		/// <summary>
		/// Shut down WorldManager and required dependencies. 
		/// Deletes all game objects stored within.
		/// </summary>
		void shutDown() override;

		/// <summary>
		/// Insert a object into the world, return 0 if ok, -1 else.
		/// Note: doesn't prevent adding the same pointer address twice.
		/// </summary>
		int insertObject(Object* p_o);

		/// <summary>
		/// Remove a object from the world, but don't delete it, return 0 if ok, -1 else.
		/// </summary>
		int removeObject(Object* p_o);

		/// <summary>
		/// Return referance to all the objects in the world.
		/// </summary>
		 ObjectList& getAllObjects();

		/// <summary>
		/// Return referance to all the objects in the world of a given subclass type(doesn't get children).
		/// </summary>
		 ObjectList objectsOfType(std::string type);

		/// <summary>
		/// Update all objects in the world. Delete any objects marked for deleation.
		/// </summary>
		void update();

		/// <summary>
		/// Draw all objects in the world.
		/// </summary>
		void draw();

		/// <summary>
		/// Mark the specified object for deletion. Delete it on next call of 'update'. 
		/// Return 0 if object not already marked, -1 if already marked.
		/// Note: the object must be in the world objects list for defined behavior.
		/// </summary>
		int markForDelete(Object* p_o);

		/// <summary>
		/// Finds all collisions this object has with all other solid objects a position where.
		/// Assumes this object is solid.
		/// </summary>
		/// <returns>A ObjectList of objects that are collided with.</returns>
		ObjectList getCollisions(const Object* p_o, Vector where);

		/// <summary>
		/// Attempt to move object according to its velocity. If object is 
		/// colliding with solid and is solid, move is not okay and send collision events.
		/// </summary>
		/// <returns>Return 0 if successfully moves, -1 if collides and doesn't move.</returns>
		int moveObject(Object* p_o, Vector where);
	};
}