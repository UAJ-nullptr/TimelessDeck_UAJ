#include "FilePersistence.h"
#include "../events/GenericEvent.h"
#include <chrono>
#include "iostream"
#include "random"

FilePersistence::FilePersistence(std::string appName, int sessionId, long long epoc) : first(true)
{
	filename = "../Game/src/data/telemetry/" + appName + "-" + std::to_string(sessionId) + "-" + std::to_string(epoc) + ".json";
	file = new std::ofstream(filename);
	if (!file->is_open()) {
		std::cout << "Telemetry file creation error.\n";
		delete file;
		file = nullptr;
	}
	else
		*file << "[\n";
}

FilePersistence::~FilePersistence()
{
	// Cerramos el archivo
	if (file != nullptr) {
		*file << "\n]";
		file->close();
		delete file;
	}	
}

void FilePersistence::flush()
{
	if (file != nullptr) {
		// serialización 
		std::string s;
		while (events.size() > 0) {
			if (!first) s += ",\n";
			s += "\t" + serializer->serialize(events.front());
			GenericEvent* gE = events.front();
			delete gE;
			events.pop();
			first = false;
		}
		*file << s;
	}
}
