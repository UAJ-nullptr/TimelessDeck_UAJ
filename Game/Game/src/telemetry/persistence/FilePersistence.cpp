#include "FilePersistence.h"
#include "../events/GenericEvent.h"
#include <chrono>
#include "iostream"
#include "random"


FilePersistence::FilePersistence(std::string appName, SerializerType sType, int sessionId, long long epoc) :
	IPersistence(sType), first(true)
{
	std::string extension = "";

	switch (serType) 
	{
	case JSON_SER:
		extension = ".json";
		break;
	case CSV_SER:
		extension = ".csv";
		break;
	case YAML_SER:
		extension = ".yaml";
		break;
	default:
		extension = ".json";
		break;
	}

	filename = "../../telemetry/" + appName + "-" + std::to_string(sessionId) + "-" + std::to_string(epoc) + extension;
	file = new std::ofstream(filename);
	
	if (!file->is_open()) {
		delete file;
		file = nullptr;
		throw ofstream::failure("Telemetry file creation error.\n");
	}
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


