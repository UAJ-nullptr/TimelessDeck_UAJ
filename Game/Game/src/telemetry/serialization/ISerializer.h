#pragma once

#include <string>
#include "../events/GenericEvent.h"
#include "queue"

class ISerializer
{
private:
	
public:
	ISerializer();
	~ISerializer();

	virtual std::string startSerializing();
	virtual std::string serialize(std::queue<GenericEvent*>* event);
	virtual std::string finishSerializing();
};

