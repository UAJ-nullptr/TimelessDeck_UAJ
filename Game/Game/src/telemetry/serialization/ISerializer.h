#pragma once

#include <string>
#include "../events/GenericEvent.h"
#include "../DQueue.h"

using EventQueue = DQueue<GenericEvent*,500>;

class ISerializer
{
private:
	
public:
	ISerializer();
	~ISerializer();

	virtual std::string startSerializing();
	virtual std::string serialize(EventQueue* event);
	virtual std::string finishSerializing();
};

