#include "FilePersistence.h"
#include "../events/GenericEvent.h"
#include <chrono>
#include <iostream>
#include <random>
#include <direct.h> 
#include <sys/stat.h>

FilePersistence::FilePersistence(std::string appName, SerializerType sType, int sessionId, long long epoc) :
	IPersistence(sType), first(true)
{
	this->appName = appName;
	this->sessionId = sessionId;
	this->epoc = epoc;
	file = nullptr;
}

FilePersistence::~FilePersistence()
{
	if (file != nullptr) {
		*file << serializer->finishSerializing();
		file->flush();
		file->close();
		delete file;
	}	
}

bool FilePersistence::init()
{
	std::string extension = serializer->getExtension();


	// Crear directorio
	string dir = "telemetry";
	struct stat info;
	// Comprobar si existe
	if (stat(dir.c_str(), &info) != 0) {
		// Si se ha entrado aquí, no existe, así que lo creamos
		if (_mkdir(dir.c_str()) != 0) {
			return false;
		}
	}

	filename = "telemetry/" + appName + "-" + std::to_string(sessionId) + "-" + std::to_string(epoc) + extension;
	file = new std::ofstream(filename);

	if (!file->is_open()) {
		delete file;
		file = nullptr;
		return false;
	}
	return true;
}

void FilePersistence::flush()
{
	if (file != nullptr) {
		std::string s = "";
		if (first) {
			s += serializer->startSerializing();
			first = false;
		}
		s += serializer->serialize(&events);
		*file << s;
	}
}


