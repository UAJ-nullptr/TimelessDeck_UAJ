#pragma once
#include "IPersistence.h"

class ServerPersistence : public IPersistence
{
private:

public:
	ServerPersistence();
	~ServerPersistence();

	virtual void flush();
};