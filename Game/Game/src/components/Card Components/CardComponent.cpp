#include "CardComponent.h"
#include "../../data/PlayerData.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/BattleScene.h"
#include "../../sdlutils/InputHandler.h"
#include "../../scenes/BattleScene.h"
#include "../../gameObjects/UI/CardCounter.h"
#include "../../gameObjects/Card Objects/Cards.h"
#include "../../scenes/TutorialScene.h"

//Constructor CardComponent, carga todos los datos del Player Data
CardComponent::CardComponent(bool tuto) : gmCtrl_(gmCtrl()), lastAbilityTime(0) {
	maxMana = PlayerData::instance()->getMaxMana();
	mana = PlayerData::instance()->getMaxMana();
	attackMult = PlayerData::instance()->getAttackMult();
	fireRateMult = PlayerData::instance()->getFireRateMult();

	if(tuto) {
		tutorialInitCard = new SwordCard();
		deck.push_back(tutorialInitCard);
	}
	_myCounter = nullptr;
	tutorial = tuto;
	system = false;
	initDeck();
}

CardComponent::~CardComponent() {
	for (Card*& c : deck) {
		delete c;
		c = nullptr;
	}
	for (Card*& c : hand) {
		delete c;
		c = nullptr;
	}
	for (Card*& c : pile) {
		delete c;
		c = nullptr;
	}
}

//Obtiene las referencias a otros componentes y escenas necesarias
void CardComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
	where = dynamic_cast<BattleScene*>(gStt);
}

//Reduce el tiempo de disparo
void CardComponent::update() {
	if (mana != PlayerData::instance()->getCurrMana()) {
		mana = PlayerData::instance()->getCurrMana();
	}
	
	if (downTime > 0) {
		downTime -= SDLApplication::instance()->getDeltaTimeSeconds();
	}
	//Si estás en automatic atacas
	if (automatic){
		attack(tr->getCenter(), InputHandler::instance()->getMousePos());
		//Si es el último uso se desbloquea la carta y desactiva el automatic
		if ((*active)->getUses() == 1) {
			discardCard(active);
			automatic = false;
			locked = false;
		}
	}
}

//Coge el imput del teclado y ratón y llama a los métodos necesarios
void CardComponent::handleInput() {
	attacking = false;
	abiliting = false;
}

//Checkea el tiempo de espera entre disparos y llama al metodo ataque de la carta activa, gestionando su municion
void CardComponent::attack(Vector2D playerPos, Vector2D mousePos) {
	if (downTime <= 0) {
		(*active)->attack(playerPos, mousePos, attackMult, where);
		(*active)->use();
		where->changeAmmoUI(active);
		downTime = (*active)->getDownTime() / fireRateMult;
		if ((*active)->getUses() <= 0) discardCard(active);
		attacking = true;
	}
}
void CardComponent::attack() {
	attack(tr->getCenter(), InputHandler::instance()->getMousePos());
}

//Checkea el mana necesario y llama al metodo habilidad de la carta activa, descartandola y consumiendo mana
void CardComponent::ability(Vector2D playerPos, Vector2D mousePos) {
	if ((*active)->getMana() <= mana && SDL_GetTicks() - lastAbilityTime > 750) {
		(*active)->ability(playerPos, mousePos, attackMult, where);
		mana -= (*active)->getMana();
		PlayerData::instance()->setCurrMana(mana);
		if((*active)->getUses() <= 0) discardCard(active);
		where->onManaChanges(mana);
		abiliting = true;
		lastAbilityTime = SDL_GetTicks();

		TelemetryTracker::instance()->addEvent(EventType::ABILITY_USED, PlayerData::instance()->getLevel());
	}
	else 
	{
		TelemetryTracker::instance()->addEvent(EventType::NOT_ENOUGH_MANA, mana, (*active)->getMana());
	}
}

void CardComponent::ability() {
	ability(tr->getCenter(), InputHandler::instance()->getMousePos());
}

//Mueve el puntero de la carta activa, dependiendo del valor de left lo mueve hacia la derecha o hacia la izquerda
void CardComponent::switchActive(bool left) {
	if (hand.size() > 1) {
		if (left && active != hand.begin()) {
			--active;
			where->changeUISelected(false, -1);
		}
		else if (!left && active != prev(hand.end())) {
			++active;
			where->changeUISelected(false, 1);
		}
	}
	
	TelemetryTracker::instance()->addEvent(EventType::CARD_CHANGED, PlayerData::instance()->getLevel());
}

void CardComponent::selectLeft() {
	switchActive(true);
}
void CardComponent::selectRight() {
	switchActive(false);
}

void CardComponent::setInitialDeck() {
	delete tutorialInitCard;
	tutorialInitCard = nullptr;
	hand.clear();
	tutorial = false;
	initDeck();
	system = true;
}

//Mueve el puntero de la carta activa a la que ocupa la posicion number, comprobando siempre que este sea válido
void CardComponent::switchActive(int number) {
	if (number >= 0 && number < hand.size()) {
		active = hand.begin();
		std::advance(active, number);
		where->changeUISelected(true, number);
	}
	
	TelemetryTracker::instance()->addEvent(EventType::CARD_CHANGED, PlayerData::instance()->getLevel());
}

//Baraja el mazo y roba la mano inicial
void CardComponent::initDeck() {
	if (!tutorial) {
		for (CardId card : PlayerData::instance()->getDeck()) {
			deck.push_back(Card::getCard(card));
		}
	}
	random_shuffle(deck.begin(), deck.end());
	newHand();
}

void CardComponent::reshufflePile() {
	//Copia y mezcla
	pile.swap(deck);
	random_shuffle(deck.begin(), deck.end());
}

void CardComponent::newHand() {
	//Si la mano esta vacia se barajan nuevas cartas
	if (deck.size() == 0)
		reshufflePile();
	if (tutorial) {
		drawCard();
	}
	else {
		if (system) {
			dynamic_cast<TutorialScene*>(gStt)->notifyNewHand();
			system = false;
		}
		for (int i = 0; i < 4; i++) {
			drawCard();
			//Si se vacia la mano al ir sacando cartas
			if (deck.size() == 0) {
				//Si tengo un contador asignado muestro la animacion de barajar
				if (_myCounter != nullptr) _myCounter->showShuffle();
				reshufflePile();
			}
		}
	}
	active = hand.begin();
}

//Añade la primera carta del mazo a la mano y la borra del mazo
void CardComponent::drawCard() {
	hand.push_back(deck.back());
	deck.pop_back();
}

//Añade una carta de la mano a la pila y la borra de la mano, reseteando sus balas y comprobando si la mano queda vacía
void CardComponent::discardCard(deque<Card*>::iterator discarded) {
	if (tutorial) {
		dynamic_cast<TutorialScene*>(gStt)->notifyDiscard();
	}
	pile.push_back(*discarded);
	(*discarded)->resetCard();
	where->discardUI(discarded);
	hand.erase(discarded);
	active = hand.begin();
	if (active != hand.begin())
		--active;
	if (hand.size() <= 0) {
		newHand();
		where->recreateUI();
	}
}