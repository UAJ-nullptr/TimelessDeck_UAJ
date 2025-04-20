#pragma once
#include "IPersistence.h"

class ServerPersistence : public IPersistence
{
private:

public:
	ServerPersistence();
	~ServerPersistence();

	void flush();
};