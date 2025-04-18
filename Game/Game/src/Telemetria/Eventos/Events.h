#pragma once
#include "GenericEvent.h"
#include "../../components/ecs.h"
#include <vector>
class SessionStartedEvent: public GenericEvent
{
private:

public:
	SessionStartedEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID) :
		GenericEvent(evntId, timeStmp, START_SESSION, appName, appVrs, sessionID) {}
};

class SessionEndedEvent : public GenericEvent
{
public:
	SessionEndedEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID) :
		GenericEvent(evntId, timeStmp, END_SESSION, appName, appVrs, sessionID) {}
};

class LevelStartedEvent : public GenericEvent
{
private:
	int LevelId;
public:
	LevelStartedEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, START_LEVEL, appName, appVrs, sessionID), LevelId(levelid) {}
};

class LevelEndedEvent : public GenericEvent
{
public:
private:
	int LevelId;
	LevelEndedEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, END_LEVEL, appName, appVrs, sessionID), LevelId(levelid) {}
};

class ChangedCardPlayingEvent : public GenericEvent
{
public:
private:
	int levelId;
	CardId currentCard;
	ChangedCardPlayingEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int levelid, CardId card) :
		GenericEvent(evntId, timeStmp, CARD_CHANGED, appName, appVrs, sessionID), levelId(levelid), currentCard(card) {}
};

class AbilityUsedEvent : public GenericEvent
{
public:
private:
	int levelId; // Para poder saber habilidadesUsadas/nivel (???)
	CardId cardFromAbility;
	AbilityUsedEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int levelid, CardId card) :
		GenericEvent(evntId, timeStmp, ABILITY_USED, appName, appVrs, sessionID), levelId(levelid), cardFromAbility(card) {}
};

class PlayerHealedEvent : public GenericEvent
{
public:
private:
	int quantityHealed; 
	PlayerHealedEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int heal) :
		GenericEvent(evntId, timeStmp, PLAYER_HEALED, appName, appVrs, sessionID), quantityHealed(heal) {}
};

class PeriodicHealthEvent : public GenericEvent
{
public:
private:
	int healthStatus;
	PeriodicHealthEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int currentHealth) :
		GenericEvent(evntId, timeStmp, PERIODIC_HEALTH_STATUS, appName, appVrs, sessionID), healthStatus(currentHealth) {}
};

class InsufficientManaEvent : public GenericEvent
{
public:
private:
	int manaStatus;
	CardId cardFromAbility;
	int manaCost;
	InsufficientManaEvent(int evntId, long long timeStmp, string appNme, string appVrs, 
		long sessionID, int currentMana, CardId ability, int abilityCost) :
		GenericEvent(evntId, timeStmp, NOT_ENOUGHT_MANA, appName, appVrs, sessionID), manaStatus(currentMana), 
		cardFromAbility(ability), manaCost(abilityCost) {}
};

class ManaTakenEvent : public GenericEvent
{
public:
private:
	int manaStatus;
	int manaTaken;
	ManaTakenEvent(int evntId, long long timeStmp, string appNme, string appVrs,
		long sessionID, int currentMana, CardId ability, int takenMana) :
		GenericEvent(evntId, timeStmp, MANA_TAKEN, appName, appVrs, sessionID), manaStatus(currentMana),
		manaTaken(takenMana) {}
};


class CanExitLevelEvent : public GenericEvent
{
public:
private:
	int LevelId;
	CanExitLevelEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int levelid) :
		GenericEvent(evntId, timeStmp, LEVEL_EXIT_POSSIBLE, appName, appVrs, sessionID), LevelId(levelid) {}
};

//class LevelExited : public GenericEvent
//{
//public:
//private:
//	int LevelId;
//	CanExitLevelEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int levelid) :
//		GenericEvent(evntId, timeStmp, LEVEL_EXIT_POSSIBLE, appName, appVrs, sessionID), LevelId(levelid) {}
//};

class TriedExitEvent : public GenericEvent
{
public:
private:
	int LevelId;
	int eterStatus;
	TriedExitEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, int levelid, int currentEter) :
		GenericEvent(evntId, timeStmp, TRIED_LEAVING, appName, appVrs, sessionID), LevelId(levelid), eterStatus(currentEter) {}
};

class ChangedCardDeckToHandEvent : public GenericEvent
{
public:
private:
	CardId cardChanged;
	ChangedCardDeckToHandEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID,CardId card) :
		GenericEvent(evntId, timeStmp, MOVED_TO_HAND, appName, appVrs, sessionID), cardChanged(card) {}
};

class ChangedCardHandToDeckEvent : public GenericEvent
{
public:
private:
	CardId cardChanged;
	ChangedCardHandToDeckEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, CardId card) :
		GenericEvent(evntId, timeStmp, MOVED_FROM_HAND, appName, appVrs, sessionID), cardChanged(card) {}
};

class InventoryExitedEvent : public GenericEvent
{
public:
private:
	vector<CardId> currentDeck;
	InventoryExitedEvent(int evntId, long long timeStmp, string appNme, string appVrs, long sessionID, vector<CardId> card) :
		GenericEvent(evntId, timeStmp, INVENTORY_LEFT, appName, appVrs, sessionID), currentDeck(card) {}
};
