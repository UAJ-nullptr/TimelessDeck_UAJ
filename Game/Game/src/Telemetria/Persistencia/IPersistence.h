#pragma once

#include "../Eventos/GenericEvent.h"

class IPersistence
{
private:

public:
	IPersistence();
	~IPersistence();

	void send(GenericEvent event);

	void flush();
};

