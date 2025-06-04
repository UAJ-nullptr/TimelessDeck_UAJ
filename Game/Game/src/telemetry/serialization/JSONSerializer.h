#pragma once
#include "ISerializer.h"

class JSONSerializer : public ISerializer
{ 
private:

public:
	JSONSerializer();
	~JSONSerializer();

	virtual std::string startSerializing();
	virtual std::string serialize(std::queue<GenericEvent*>* event);
	virtual std::string finishSerializing();
};

