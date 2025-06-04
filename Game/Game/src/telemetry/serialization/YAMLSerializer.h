#pragma once
#include "ISerializer.h"

class YAMLSerializer : public ISerializer
{
private:

public:
	YAMLSerializer();
	~YAMLSerializer();

	virtual std::string serialize(std::queue<GenericEvent*>* event);
};

