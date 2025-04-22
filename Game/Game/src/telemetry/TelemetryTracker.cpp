#include "TelemetryTracker.h"
#include "persistence/FilePersistence.h"
#include <cstdarg>

TelemetryTracker::TelemetryTracker() : appName("null"), appVersion("0"), sessionId(0), currentId(0), elapsedTime(0),
	timeLimit(0), persistence(nullptr)
{

}

TelemetryTracker::TelemetryTracker(string appName, string appVers, double timeLimit) : appName(appName),
	appVersion(appVers), sessionId(sessionId), currentId(0), elapsedTime(0), timeLimit(timeLimit)
{
    long long epoc = getEpocTimestamp();
    sessionId = epoc / pow(10, 12);
    sessionId /= rand() % 100 + 100;

	persistence = new FilePersistence(appName, sessionId, epoc);
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
		// volcado a disco a traves de persistencia
		persistence->flush();

		elapsedTime = 0;
	}
}

void TelemetryTracker::flush()
{
	persistence->flush();
}

void TelemetryTracker::addEvent(EventType type, ...)
{
    auto time = std::chrono::system_clock::now();
    long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
        time.time_since_epoch()).count();
    va_list args;
    va_start(args, type);

    switch (type)
    {
    case START_SESSION:
        persistence->send(new SessionStartedEvent(currentId, timeInNano, appName, appVersion, sessionId));
        break;
    case END_SESSION:
        persistence->send(new SessionEndedEvent(currentId, timeInNano, appName, appVersion, sessionId));
        break;
    case START_LEVEL:
        persistence->send(new LevelStartedEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args,int)));
        break;
    case END_LEVEL:
        persistence->send(new LevelEndedEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, int)));
        break;
    case CARD_CHANGED:
        persistence->send(new ChangedCardPlayingEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, int), va_arg(args, CardId)));
        break;
    case ABILITY_USED:
        persistence->send(new AbilityUsedEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, int), va_arg(args, CardId)));
        break;
    case PLAYER_HEALED:
        persistence->send(new PlayerHealedEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, int)));
        break;
    case PERIODIC_HEALTH_STATUS:
        persistence->send(new PeriodicHealthEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, int)));
        break;
    case MANA_TAKEN:
        persistence->send(new ManaTakenEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, int), va_arg(args, int)));
        break;
    case NOT_ENOUGH_MANA:
        persistence->send(new InsufficientManaEvent(currentId, timeInNano, appName, appVersion, sessionId,
            va_arg(args, int), va_arg(args, CardId), va_arg(args, int)));
        break;
    case LEVEL_EXIT_POSSIBLE:
        persistence->send(new CanExitLevelEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, int)));
        break;
    case TRIED_LEAVING:
        persistence->send(new TriedExitEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, int)));
        break;
    case MOVED_FROM_HAND:
        persistence->send(new ChangedCardHandToDeckEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, CardId)));
        break;
    case MOVED_TO_HAND:
        persistence->send(new ChangedCardDeckToHandEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, CardId)));
        break;
    case INVENTORY_LEFT:
        persistence->send(new InventoryExitedEvent(currentId, timeInNano, appName, appVersion, sessionId, va_arg(args, vector<CardId>)));
        break;
    }
    va_end(args);
    currentId++;
}


