#pragma once
#include "queue"
#include "../Serialización/ISerializer.h"
#include "../Eventos/Events.h"

class IPersistence
{
protected:
	std::queue<GenericEvent*> events;
	ISerializer serializer;
public:
	IPersistence();
	virtual ~IPersistence();

	virtual void send(GenericEvent* event);

	virtual void flush();
};

