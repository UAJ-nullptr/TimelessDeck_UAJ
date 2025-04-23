#pragma once
#include "ISerializer.h"

class CSVSerializer : public ISerializer
{
private:

public:
	CSVSerializer();
	~CSVSerializer();

	virtual std::string serialize(GenericEvent* event);
};

