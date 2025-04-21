#pragma once

#include <string>
#include "../Eventos/Events.h"

class ISerializer
{
private:
	
public:
	ISerializer();
	~ISerializer();

	virtual std::string serialize(GenericEvent* event);
};

