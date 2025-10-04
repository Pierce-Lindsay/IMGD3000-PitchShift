#include "WorldManager.h"
#include "../LogManager.h"
#include "../graphics/DisplayManager.h"
#include "../Utility.h"
#include "EventCollision.h"
#include "EventOut.h"
#include <vector>

using namespace df;

WorldManager::WorldManager()
{
	setType("WorldManager");
}

WorldManager::~WorldManager()
{

}

WorldManager& WorldManager::GetInstance()
{
	static WorldManager wm;
	return wm;
}

int WorldManager::startUp()
{
	//needs lm for logging, if isn't started, start it
	if (!LM.isStarted())
	{
		if (LM.startUp() == -1)
			return -1;
	}

	LM.writeLog("WorldManager::startUp::WorldManager start up successful.");
	m_updates.clear();
	m_deletions.clear();
	return Manager::startUp();
}

void WorldManager::shutDown()
{
	m_deletions.clear();
	for (int i = 0; i < m_updates.getCount(); i++)
	{
		delete m_updates[i]; //removed as soon as deleted
		i--;
	}
	m_updates.clear();
	LM.writeLog("WorldManager::shutDown::WorldManager shutdown successfully!");
	Manager::shutDown();
}

int WorldManager::insertObject(Object* p_o)
{
	if (!isStarted())
		throw std::runtime_error::exception("Can't insert object when world manager isn't started!");
	if (m_updates.insert(p_o) == -1)
	{
		int id = p_o->getID();
		std::string type = p_o->getType();
		LM.writeLog("WorldManager::insertObject::Failed to add object with adress: %p, type: %s, and id: %d because the ObjectList was full.", p_o, type.c_str(), id);
		return -1;
	}
	return 0;
}

int WorldManager::removeObject(Object* p_o)
{
	if (!isStarted())
		throw std::runtime_error::exception("Can't remove object when world manager isn't started!");
	//remove from updates but don't delete
	if (m_updates.remove(p_o) == -1)
	{
		int id = p_o->getID();
		std::string type = p_o->getType();
		LM.writeLog("WorldManager::removeObject::Failed to remove object with adress: %p, type: %s, and id: %d because it wasn't found.", p_o, type.c_str(), id);
		return -1;
	}
	return 0;
}

ObjectList& WorldManager::getAllObjects() 
{
	return m_updates;
}

ObjectList WorldManager::objectsOfType(std::string type)
{
	if (!isStarted())
		throw std::runtime_error::exception("Can't get objects when world manager isn't started!");

	ObjectList elements_of_type;
	for (int i = 0; i < m_updates.getCount(); i++)
	{
		if (m_updates[i]->getType() == type)
			elements_of_type.insert(m_updates[i]);
	}
	return elements_of_type; //because on stack, can't return referance
}

void WorldManager::update()
{
	if (!isStarted())
		throw std::runtime_error::exception("Can't update objects when world manager isn't started!");

	//delete all marked objects
	for (int i = 0; i < m_deletions.getCount(); i++)
	{
		delete m_deletions[i]; //when an object is deleted it removes itself from m_updates
	}
	m_deletions.clear();

	//now update physics
	for (int i = 0; i < m_updates.getCount(); i++)
	{
		Vector old_pos = m_updates[i]->getPosition();
		Vector new_pos = m_updates[i]->predictPosition();
		if (new_pos.x != old_pos.x || new_pos.y != old_pos.y)
		{
			//if we actually moved, check collisions
			moveObject(m_updates[i], new_pos);
		}
		//check if out bounds (screen for now), placed here to catch 
		// objects that spawn out of bounds originally
		if (new_pos.x < 0 || new_pos.x > DM.getHorizontalChars()
			|| new_pos.y < 0 || new_pos.y > DM.getVerticalChars())
		{
			EventOut e;
			m_updates[i]->eventHandler(&e);
		}
	}
}

void WorldManager::draw()
{
	if (!isStarted())
		throw std::runtime_error::exception("Can't draw objects when world manager isn't started!");
	else if (!DM.isStarted())
		throw std::runtime_error::exception("Can't draw objects when display manager isn't started!");

	//now draw
	//split into altitudes that loop through groups
	const int bin_count = 1 + MAX_ALTITUDE - MIN_ALTITUDE;
	std::vector<Object*> bins[bin_count];
	//note: I dont know if this is fater than the alternative but my gut says it scales better
	for (int i = 0; i < m_updates.getCount(); i++)// we can sort in 0(n) because discrete # of bins
	{
		bins[m_updates[i]->getAltitude()].push_back(m_updates[i]);
	}

	for (int i = 0; i < bin_count; i++) //bins are now ordered, loop through
	{
		for (int j = 0; j < bins[i].size(); j++)
		{
			bins[i][j]->draw();
		}
		bins[i].clear();
	}
}

int WorldManager::markForDelete(Object* p_o)
{
	if (!isStarted())
		throw std::runtime_error::exception("Can't delete objects when world manager isn't started!");

	if (p_o->getMarkForDelete())
		return -1; //already marked
	else
	{ //note: assumes object is alread in m_updates
		if (m_deletions.insert(p_o) == -1)
		{
			int id = p_o->getID();
			std::string type = p_o->getType();
			LM.writeLog("WorldManager::markForDelete::Failed to add object to deletion list with adress: %p, type: %s, and id: %d because the deletion list was full.", p_o, type.c_str(), id);
			return -1;
		}
		p_o->setMarkForDelete(true); //only mark if we can actually add to deletions
		return 0;
	}
}

ObjectList WorldManager::getCollisions(const Object* p_o, Vector where)
{
	ObjectList collisions;
	Box b1 = getWorldBox(p_o, where);

	for (int i = 0; i < m_updates.getCount(); i++)
	{
		Object* temp = m_updates[i];
		if (temp != p_o && temp->isSolid()) //skip self
		{
			//if will be in the same location <= +-1, collision
			Box b2 = getWorldBox(temp);

			if (boxIntersectsBox(b1, b2)) 
				collisions.insert(temp);
		}
	}
	return collisions;
}

int WorldManager::moveObject(Object* p_o, Vector where)
{
	if (!p_o->isSolid())
	{
		p_o->setPosition(where);
		return 0;
	}
	ObjectList collisions = getCollisions(p_o, where);
	if (collisions.getCount() == 0)
	{
		p_o->setPosition(where);
		return 0;
	}
	int should_move = 0;
	Solidness s1 = p_o->getSolidness();
	for (int i = 0; i < collisions.getCount(); i++)
	{
		Object* temp = collisions[i];
		EventCollision e_c(p_o, temp, where);
		p_o->eventHandler(&e_c);
		temp->eventHandler(&e_c);
		if (temp->getSolidness() == Solidness::HARD && s1 == Solidness::HARD)
			should_move = -1;
	}

	if (should_move == 0)
		p_o->setPosition(where);
	return should_move;
}