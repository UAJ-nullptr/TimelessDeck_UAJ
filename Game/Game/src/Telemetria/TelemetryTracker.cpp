#include "TelemetryTracker.h"

TelemetryTracker::TelemetryTracker(string appName, string appVers, int sessionId)
{
	currentId = 0;
	this->appName = appName;
	this->appVersion = appVers;
	this->sessionId = sessionId;
}

TelemetryTracker::~TelemetryTracker()
{

}

void TelemetryTracker::addEvent(GenericEvent event)
{
	events.push(event);
}

void TelemetryTracker::addSessionStartedEvent()
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(SessionStartedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId));
	currentId++;
}

void TelemetryTracker::addSessionEndedEvent()
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(SessionEndedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId));
	currentId++;
}

void TelemetryTracker::addLevelStartedEvent(int levelId)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(LevelStartedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId,levelId));
	currentId++;
}

void TelemetryTracker::addLevelEndedEvent(int levelId)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(LevelEndedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId,levelId));
	currentId++;
}

void TelemetryTracker::addChangedCardEvent(int levelId, CardId card)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(ChangedCardPlayingEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, levelId, card));
	currentId++;
}

void TelemetryTracker::addAbilityUsedEvent(int levelId, CardId card)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(AbilityUsedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, levelId, card));
	currentId++;
}

void TelemetryTracker::addPlayerHealedEvent(int heal)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(PlayerHealedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, heal));
	currentId++;
}

void TelemetryTracker::addPeriodicHealthStatusEvent(int health)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(PeriodicHealthEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, health));
	currentId++;
}

void TelemetryTracker::addInsuficientManaEvent(int currentMana, CardId cardAbility, int abilityCost)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(InsufficientManaEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, 
		currentMana,cardAbility,abilityCost));
	currentId++;
}

void TelemetryTracker::addManaTakenEvent(int currentMana, int manaTaken)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(ManaTakenEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, currentMana,manaTaken));
	currentId++;
}

void TelemetryTracker::addExitPossibleEvent(int levelId)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(CanExitLevelEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, levelId));
	currentId++;
}

void TelemetryTracker::addTriedExitEvent(int levelId, int currentEter)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(TriedExitEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, levelId, currentEter));
	currentId++;
}

void TelemetryTracker::addChangedToHandEvent(CardId card)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(ChangedCardDeckToHandEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, card));
	currentId++;
}

void TelemetryTracker::addChangedToDeckEvent(CardId card)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(ChangedCardHandToDeckEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, card));
	currentId++;
}

void TelemetryTracker::addInventoryExitedEvent(vector<CardId> deck)
{
	auto time = chrono::system_clock::now();
	long long timeInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(
		time.time_since_epoch()).count();
	events.push(InventoryExitedEvent(currentId, timeInNano, this->appName, this->appVersion, this->sessionId, deck));
	currentId++;
}

GenericEvent TelemetryTracker::getOldestEvent()
{
	GenericEvent oldestEvent = events.front();
	events.pop();
	return oldestEvent;
}


