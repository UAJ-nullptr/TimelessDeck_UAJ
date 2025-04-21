#include "FilePersistence.h"
#include "../Eventos/GenericEvent.h"
#include <chrono>
#include "iostream"

FilePersistence::FilePersistence(int sessionId) : first(true)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();

	filename = "../Game/src/data/telemetry/" + std::to_string(sessionId) + "-" + std::to_string(timeInNano) + ".json";
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
