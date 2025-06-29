#pragma once
#include "IPersistence.h"
#include <fstream>

class FilePersistence : public IPersistence
{
private:
	std::string filename;

	std::ofstream* file;

	bool first;
	std::string appName;
	int sessionId;
	long long epoc;

public:
	FilePersistence(std::string appName, SerializerType sType, int sessionId, long long epoc);
	~FilePersistence();

	virtual bool init();
	virtual void flush();
};