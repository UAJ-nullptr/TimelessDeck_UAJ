#pragma once
#include "../utils/Singleton.h"
#include "../gameObjects/Card Objects/Card.h"
#include "../data/CardsDataContainer.h"
#include "../data/RelicData.h"
#include <vector>
#include <map>
#include <list>
#include <string>



class Card;
class PlayerData : public Singleton<PlayerData>
{
	friend Singleton<PlayerData>;

	private:
	
	/*
	
	Mazo - lo que se lleva
	Biblioteca - lo que no
	Inventario - TODO
	Cartas Recibidas - Mapa de cartas recibidas y su posicion en el vector de inventario

	Progreso de la run
	- mapa
	- posicion
	- currentStats
	- items
	
	
	*/

	std::vector<CardId> library;
	std::vector<CardId> deck;
	
	CardId lastCard;
	
	//Vector con todas las reliquias disponibles, saca su key del mapa
	std::vector<std::string> avlbRelics;

	//Vector con las reliquias que tiene el jugador
	std::vector<Relic*> myRelics;

	int money;
	int maxMana;
	int maxHP;
	int currHP;
	int currMana;
	float playerSpeed;

	float attackMult, fireRateMult;
	
	int level;

	bool cardGained, inventoryNotOpen;

	PlayerData();

	public:
		inline int getMaxMana() { return maxMana; }
		inline int getCurrMana() { return currMana; }
		inline void resetMana() { currMana = maxMana; }
		inline int getMaxHP() { return maxHP; }
		inline int getCurrHP() { return currHP; }
		inline float getAttackMult() { return attackMult; }
		inline float getFireRateMult() { return fireRateMult; }
		inline float getPlayerMoveSpeed() { return playerSpeed; }
		inline float getMoney() { return money; }
		inline int getLevel() { return level; }
		inline vector<Relic*> getRelics() { return myRelics; }
		inline void setCardGained(bool value) { cardGained = value; }
		inline bool getCardGained() { return cardGained; }
		inline void setInventoryOpen(bool value) { inventoryNotOpen = value; }
		inline bool getInventoryOpen() { return inventoryNotOpen; }

		inline void setMoney(int newMoney) { money = newMoney; }
		inline void setMaxMana(int newMaxMana) { maxMana = newMaxMana; }
		inline void setCurrMana(int newCurrMana) { currMana = newCurrMana; }
		inline void setMaxHP(int newMaxHP) { maxHP = newMaxHP; }
		inline void setCurrHP(int newCurrHP) { currHP = newCurrHP; }
		inline void setAttackMult(float newAttackMult) { attackMult = newAttackMult; }
		inline void setFireRateMult(float newFireRateMult) { fireRateMult = newFireRateMult; }
		inline void setLevel(int newLevel) { level = newLevel; }
		inline void setPlayerMoveSpeed(float newMoveSpeed) { playerSpeed = newMoveSpeed; }

		inline void addMoney(int mon) { money += mon; }
		inline void addMaxMana(int mana) { maxMana += mana; }
		inline void addCurrMana(int mana) { currMana += mana; }
		inline void addMaxHP(int hp) { maxHP += hp; }
		inline void addCurrHP(int hp) { currHP += hp; }
		inline void addAttackMult(float attack) { attackMult += attack; }
		inline void addFireRateMult(float rate) { fireRateMult += rate; }
		inline void addPlayerMoveSpeed(float speed) { playerSpeed += speed; }

		inline void nextLevel() { level++; }

		void defaultPlayerStats();

		void getDataFromJSON();
		void setDataToJSON();
		bool hasSaveFile() const;
		void loseSavedData();

		std::vector<std::string> getAvailableItems();
		void setAvailableItems(std::vector<std::string> newItems);

		pair<CardId, int> getNewCard();

		bool cardAvailable();

		void addRelic(Relic* relic);

		void addCardToLibrary(CardId newCard, int num);
		std::vector<CardId> const& getLibrary();

		void addCardToDeck(CardId newCard, int num);
		std::vector<CardId> const& getDeck();
		void setDeck(std::vector<CardId>);
		
};

inline PlayerData& pD() {
	return *PlayerData::instance();
}
