#pragma once
#include "IPersistence.h"
#include <fstream>

class FilePersistence : public IPersistence
{
private:
	std::string filename;

	std::ofstream* file;
public:
	FilePersistence(int sessionId);
	~FilePersistence();

	void flush();
};