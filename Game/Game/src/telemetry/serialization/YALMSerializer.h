#pragma once
#include "ISerializer.h"

class YALMSerializer : public ISerializer
{
private:

public:
	YALMSerializer();
	~YALMSerializer();

	virtual std::string serialize(GenericEvent* event);
};

