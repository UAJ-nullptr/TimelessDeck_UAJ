#pragma once
#include "ISerializer.h"

class JSONSerializer : public ISerializer
{ 
private:

public:
	JSONSerializer();
	~JSONSerializer();

	virtual std::string serialize(GenericEvent* event);
};

