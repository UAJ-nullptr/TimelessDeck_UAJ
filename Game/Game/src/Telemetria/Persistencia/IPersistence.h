#pragma once
#include "queue"
#include "../Serializaci�n/ISerializer.h"

class GenericEvent;

class IPersistence
{
protected:
	std::queue<GenericEvent> events;
	ISerializer serializer;
public:
	IPersistence();
	~IPersistence();

	void send(GenericEvent event);

	void flush();
};

