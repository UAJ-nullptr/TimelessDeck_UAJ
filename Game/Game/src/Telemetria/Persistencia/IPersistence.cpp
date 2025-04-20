#include "IPersistence.h"
#include "../Eventos/GenericEvent.h"

IPersistence::IPersistence()
{

}

IPersistence::~IPersistence()
{

}

void IPersistence::send(GenericEvent event)
{
	events.push(event);
}
