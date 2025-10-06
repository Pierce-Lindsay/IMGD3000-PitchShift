#include "ObjectList.h"
#include "../LogManager.h"

using namespace df;

ObjectList::ObjectList()
{
	//needs logmanager, start it if it's not started already
	if (!LM.isStarted())
		LM.startUp();
} //count already 0, do nothing for now


int ObjectList::insert(Object* p_o)
{
	if (count < MAX_OBJECTS)
	{
		p_obj[count] = p_o;
		count++;
		return 0;
	}
	else
	{
		int id = p_o->getID();
		std::string type = p_o->getType();
		LM.writeLog("ObjectList::insert::Failed to add object with adress: %p, type: %s, and id: %d because the ObjectList was full.", p_o, type.c_str(), id);
		return -1;
	}
}

//slow if called a bunch //swap for speed, we don't care about order
int ObjectList::remove(Object* p_o)
{
	int pos = find(p_o);
	if (pos == -1)
	{
		int id = p_o->getID();
		std::string type = p_o->getType();
		LM.writeLog("ObjectList::remove::Failed to remove object with adress: %p, type: %s, and id: %d because it wasn't found in the ObjectList.", p_o, type.c_str(), id);
		return -1; //failed to remove
	}
	else
	{
		//swap pos with past and pop off end
		p_obj[pos] = p_obj[count - 1];
		p_obj[count - 1] = NULL;
		count--;
	}
	return 0;
}

void ObjectList::clear()
{
	//the memory above count should be untouchable by user, so fastest option here is to just set count to 0.
	count = 0;
}


int ObjectList::getCount() const
{
	return count;
}


bool ObjectList::isEmpty() const
{
	return count == 0;
}

int ObjectList::find(Object* p_o) const
{
	//find pos of element in array
	int id = p_o->getID();
	for (int i = 0; i < count; i++)
	{
		if (p_obj[i]->getID() == id)
			return i;
	}
	return -1;
}


Object*& ObjectList::operator[](int index)
{
	if (index >= count || index < 0)
	{
		//force flush before error
		LM.setFlush();
		LM.writeLog("ObjectList::index::Failed to index object at position: %d, the count of the ObjectList is %d.", index, count);
		throw std::out_of_range::exception("The provided index exceeded the bounds of the ObjectList.");
	}
	else
		return p_obj[index];
}