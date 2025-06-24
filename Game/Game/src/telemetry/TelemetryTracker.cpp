#include "TelemetryTracker.h"
#include "persistence/FilePersistence.h"
#include <cstdarg>

TelemetryTracker::TelemetryTracker() : appName("null"), appVersion("0"), sessionId(0), currentId(0), elapsedTime(0),
	timeLimit(0), persistence(nullptr) {}

TelemetryTracker::TelemetryTracker(string appName, string appVers, double timeLimit) : appName(appName),
	appVersion(appVers), sessionId(sessionId), currentId(0), elapsedTime(0), timeLimit(timeLimit)
{
    long long epoc = getEpocTimestamp();
    sessionId = epoc / pow(10, 12);
    sessionId /= rand() % 100 + 100;

	persistence = new FilePersistence(appName, SerializerType::JSON_SER, sessionId, epoc);
	//persistence = new FilePersistence(appName, SerializerType::YALM_SER, sessionId, epoc);
}

TelemetryTracker::~TelemetryTracker()
{
	delete persistence;
}

long long TelemetryTracker::getEpocTimestamp()
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	return timeInNano;
}


void TelemetryTracker::update(double deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime > timeLimit) {
		persistence->flush();
		elapsedTime = 0;
	}
}

void TelemetryTracker::flush()
{
	persistence->flush();
}

void TelemetryTracker::addEvent(GenericEvent* event)
{
	auto time = std::chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()).count();
	event->setEventTimeStamp(timeInNano);
	event->setEventAppName(appName);
	event->setEventAppVersion(appVersion);
	event->setEventId(currentId);
	event->setEventSessionId(sessionId);
	persistence->send(event);
	currentId++;
}
