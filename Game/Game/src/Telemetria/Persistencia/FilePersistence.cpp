#include "FilePersistence.h"
#include "../Eventos/GenericEvent.h"
#include <chrono>
#include "iostream"

FilePersistence::FilePersistence(int sessionId) {
	// Abrir/Crear el archivo
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
}

FilePersistence::~FilePersistence()
{
	// Cerramos el archivo
	if (file != nullptr) {
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
			GenericEvent oldestEvent = events.front();
			events.pop();
			s += serializer.serialize(oldestEvent);
		}
		s = "hola\n";
		*file << s;
	}
}
