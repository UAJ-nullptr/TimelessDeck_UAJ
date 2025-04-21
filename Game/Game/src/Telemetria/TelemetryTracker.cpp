#include "TelemetryTracker.h"
#include "Persistencia/FilePersistence.h"

TelemetryTracker::TelemetryTracker()
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

void TelemetryTracker::update(double deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime > timeLimit) {
		// volcado a disco a traves de persistencia
		persistence->flush();
		//cout << deltaTime << " y " << elapsedTime << endl;
		// creo que algo no va bien con el tiempo

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
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new SessionStartedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId));
	currentId++;
}

void TelemetryTracker::addSessionEndedEvent()
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new SessionEndedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId));
	currentId++;
}

void TelemetryTracker::addLevelStartedEvent(int levelId)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new LevelStartedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId,levelId));
	currentId++;
}

void TelemetryTracker::addLevelEndedEvent(int levelId)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new LevelEndedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId,levelId));
	currentId++;
}

void TelemetryTracker::addChangedCardEvent(int levelId, CardId card)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new  ChangedCardPlayingEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, levelId, card));
	currentId++;
}

void TelemetryTracker::addAbilityUsedEvent(int levelId, CardId card)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new AbilityUsedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, levelId, card));
	currentId++;
}

void TelemetryTracker::addPlayerHealedEvent(int heal)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new PlayerHealedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, heal));
	currentId++;
}

void TelemetryTracker::addPeriodicHealthStatusEvent(int health)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new PeriodicHealthEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, health));
	currentId++;
}

void TelemetryTracker::addInsuficientManaEvent(int currentMana, CardId cardAbility, int abilityCost)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new InsufficientManaEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId,
		currentMana,cardAbility,abilityCost));
	currentId++;
}

void TelemetryTracker::addManaTakenEvent(int currentMana, int manaTaken)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new ManaTakenEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, currentMana,manaTaken));
	currentId++;
}

void TelemetryTracker::addExitPossibleEvent(int levelId)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new CanExitLevelEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, levelId));
	currentId++;
}

void TelemetryTracker::addTriedExitEvent(int levelId, int currentEter)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new TriedExitEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, levelId, currentEter));
	currentId++;
}

void TelemetryTracker::addChangedToHandEvent(CardId card)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new ChangedCardDeckToHandEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, card));
	currentId++;
}

void TelemetryTracker::addChangedToDeckEvent(CardId card)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new ChangedCardHandToDeckEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, card));
	currentId++;
}

void TelemetryTracker::addInventoryExitedEvent(vector<CardId> deck)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	persistence->send(new InventoryExitedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, deck));
	currentId++;
}


