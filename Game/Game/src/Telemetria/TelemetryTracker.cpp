#include "TelemetryTracker.h"
#include "Persistencia/FilePersistence.h"

TelemetryTracker::TelemetryTracker() : appName("null"), appVersion("0"), sessionId(0), currentId(0), elapsedTime(0),
	timeLimit(0), persistence(nullptr)
{

}

TelemetryTracker::TelemetryTracker(string appName, string appVers, int sessionId, double timeLimit) : appName(appName),
	appVersion(appVers), sessionId(sessionId), currentId(0), elapsedTime(0), timeLimit(timeLimit)
{
	persistence = new FilePersistence(sessionId);
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

void TelemetryTracker::addEvent(GenericEvent* event)
{
	persistence->send(event);
}

void TelemetryTracker::addSessionStartedEvent()
{
	persistence->send(new SessionStartedEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId));
	currentId++;
}

void TelemetryTracker::addSessionEndedEvent()
{
	persistence->send(new SessionEndedEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId));
	currentId++;
}

void TelemetryTracker::addLevelStartedEvent(int levelId)
{
	persistence->send(new LevelStartedEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId,levelId));
	currentId++;
}

void TelemetryTracker::addLevelEndedEvent(int levelId)
{
	persistence->send(new LevelEndedEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId,levelId));
	currentId++;
}

void TelemetryTracker::addChangedCardEvent(int levelId, CardId card)
{
	persistence->send(new  ChangedCardPlayingEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, levelId, card));
	currentId++;
}

void TelemetryTracker::addAbilityUsedEvent(int levelId, CardId card)
{
	persistence->send(new AbilityUsedEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, levelId, card));
	currentId++;
}

void TelemetryTracker::addPlayerHealedEvent(int heal)
{
	persistence->send(new PlayerHealedEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, heal));
	currentId++;
}

void TelemetryTracker::addPeriodicHealthStatusEvent(int health)
{
	persistence->send(new PeriodicHealthEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, health));
	currentId++;
}

void TelemetryTracker::addInsuficientManaEvent(int currentMana, CardId cardAbility, int abilityCost)
{
	persistence->send(new InsufficientManaEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId,
		currentMana,cardAbility,abilityCost));
	currentId++;
}

void TelemetryTracker::addManaTakenEvent(int currentMana, int manaTaken)
{
	persistence->send(new ManaTakenEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, currentMana,manaTaken));
	currentId++;
}

void TelemetryTracker::addExitPossibleEvent(int levelId)
{
	persistence->send(new CanExitLevelEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, levelId));
	currentId++;
}

void TelemetryTracker::addTriedExitEvent(int levelId, int currentEter)
{
	persistence->send(new TriedExitEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, levelId, currentEter));
	currentId++;
}

void TelemetryTracker::addChangedToHandEvent(CardId card)
{
	persistence->send(new ChangedCardDeckToHandEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, card));
	currentId++;
}

void TelemetryTracker::addChangedToDeckEvent(CardId card)
{
	persistence->send(new ChangedCardHandToDeckEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, card));
	currentId++;
}

void TelemetryTracker::addInventoryExitedEvent(vector<CardId> deck)
{
	persistence->send(new InventoryExitedEvent(currentId, getEpocTimestamp(), this->appName, this->appVersion, this->sessionId, deck));
	currentId++;
}


