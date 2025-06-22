#pragma once
#include "ISerializer.h"

class JSONSerializer : public ISerializer
{ 
private:
	bool first;

public:
	JSONSerializer();
	~JSONSerializer();

	virtual std::string startSerializing();
	virtual std::string serialize(EventQueue* events);
	virtual std::string finishSerializing();
};

