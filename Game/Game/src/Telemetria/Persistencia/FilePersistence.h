#pragma once
#include "IPersistence.h"
#include <fstream>

class FilePersistence : public IPersistence
{
private:
	std::string filename;

	std::ofstream* file;

	bool first;

public:
	FilePersistence(std::string appName, int sessionId, long long epoc);
	~FilePersistence();

	virtual void flush();
};