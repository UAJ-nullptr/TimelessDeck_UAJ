#include "IPersistence.h"

IPersistence::IPersistence()
{

}

IPersistence::~IPersistence()
{

}

void IPersistence::send(GenericEvent* event)
{
	events.push(event);
}

void IPersistence::flush()
{

}
