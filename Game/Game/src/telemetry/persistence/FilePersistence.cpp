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
	case YALM_SER:
		extension = ".yalm";
		break;
	default:
		extension = ".json";
		break;
	}

	filename = "../Game/src/data/telemetry/" + appName + "-" + std::to_string(sessionId) + "-" + std::to_string(epoc) + extension;
	file = new std::ofstream(filename);
	
	if (!file->is_open()) {
		std::cout << "Telemetry file creation error.\n";
		delete file;
		file = nullptr;
	}
	else {
		if (serType == SerializerType::JSON_SER) *file << "[\n";
	}
}

FilePersistence::~FilePersistence()
{
	if (file != nullptr) {

		if (serType == SerializerType::JSON_SER)
			*file << "[\n";

		file->close();
		delete file;
	}	
}

void FilePersistence::flush()
{
	if (file != nullptr) {
		std::string s;

		while (events.size() > 0) {

			if (serType == SerializerType::JSON_SER) {
				if (!first) s += ",\n";
				s += "\t";
			}
			s += serializer->serialize(events.front());

			GenericEvent* gE = events.front();
			delete gE;
			events.pop();

			first = false;
		}
		*file << s;
	}
}
