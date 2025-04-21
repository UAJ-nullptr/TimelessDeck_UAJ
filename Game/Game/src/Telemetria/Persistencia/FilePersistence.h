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
	FilePersistence(int sessionId);
	~FilePersistence();

	virtual void flush();
};