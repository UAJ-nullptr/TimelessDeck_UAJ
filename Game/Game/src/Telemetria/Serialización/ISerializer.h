#pragma once

#include <string>
#include "../Eventos/GenericEvent.h"
#include "../../data/json/JSON.h"

class ISerializer
{
private:
	JSONValue* fileJSON;
public:
	ISerializer();
	~ISerializer();

	std::string serialize(GenericEvent event);
};

