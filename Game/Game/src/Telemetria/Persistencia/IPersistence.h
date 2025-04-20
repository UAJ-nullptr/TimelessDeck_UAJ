#pragma once
#include "queue"
#include "../Serialización/ISerializer.h"

class GenericEvent;

class IPersistence
{
protected:
	std::queue<GenericEvent> events;
	ISerializer serializer;
public:
	IPersistence();
	~IPersistence();

	virtual void send(GenericEvent event);

	virtual void flush();
};

