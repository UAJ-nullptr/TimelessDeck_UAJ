#pragma once

#include <string>
#include "../Eventos/GenericEvent.h"

class ISerializer
{
private:

public:
	ISerializer();
	~ISerializer();

	std::string serialize(GenericEvent event);
};

