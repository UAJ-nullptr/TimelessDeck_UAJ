﻿#include "InventoryScene.h"
#include "../core/SDLApplication.h"
#include "../data/PlayerData.h"
#include "../components/General Components/CallbackDelayer.h"
#include "../telemetry/TelemetryTracker.h"

// Se encarga de cargar todos los datos desde el dataplayer, así como obtener los datos del deck y de la library
InventoryScene::InventoryScene() : GameState(), feedback(nullptr) {
	vector<CardId> const& currentLibrary = PlayerData::instance()->getLibrary();
	vector<CardId> const& currentDeck = PlayerData::instance()->getDeck();
	camTr = camera->getComponent<Transform>();
	cardsInDeck = 0;
	camYLimit = 50;
	for (CardId crd : currentLibrary) {
		auto invCard = inventory.find(Card::getCardIDfromEnum(crd));
		// Si la carta no está, se añade al inventario
		if (invCard == inventory.end()) {
			invCard = inventory.insert({ Card::getCardIDfromEnum(crd), InventoryInfo() }).first;
			invCard->second.card = crd;
		}
		// Aumentar su cantidad en el inventario
		++invCard->second.cuantity;
	}

	for (CardId crd : currentDeck) {
		inventory[Card::getCardIDfromEnum(crd)].cuantityDeck++;
	}

	// Llamamos a Player data para pillar la info de las cartas que se tienen
	stats.push_back(PlayerData::instance()->getMaxHP());
	stats.push_back(PlayerData::instance()->getMaxMana());
	stats.push_back(PlayerData::instance()->getPlayerMoveSpeed() / 2);
	stats.push_back(PlayerData::instance()->getAttackMult() * 100);
	stats.push_back(PlayerData::instance()->getFireRateMult() * 100);

	//Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(0,-1.33*WIN_HEIGHT), Vector2D(), WIN_WIDTH, 3*WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("InventoryBackground"));
	GameObject* background2 = addGameObject();
	background2->addComponent<Transform>(Vector2D(WIN_WIDTH-330,0), Vector2D(), 330, WIN_HEIGHT);
	background2->addComponent<Image>(SDLApplication::getTexture("InventoryBackgroundStats"))->attachToCamera();

	createMoneyInfo();
	createObjects(); 
	createCards();
	createPanels();

	// Los simbolos
	for (int i = 0; i < 5; i++) {
		createSymbol(SYMBOL_POSITIONS[i], SYMBOLS_KEYS[i], STATS_TEXTS[i], stats[i]);
	}
	for (auto& crd : inventory) {
		if (inventory[Card::getCardIDfromEnum(crd.second.card)].cuantityDeck > 0) {
			cardsInDeck += inventory[Card::getCardIDfromEnum(crd.second.card)].cuantityDeck;
		}
	}
	// Creamos el boton de salir
	AnimatorInfo aI = AnimatorInfo(EXIT);
	exitButton = addGameObject<Button>(_grp_UI,
		[&]() {
			if (cardsInDeck >= 4) SDLApplication::popGameState();
			else {
				feedback = addGameObject();
				feedback->addComponent<Transform>(FEEDBACK_POS, Vector2D(), FEEDBACK_WIDTH, FEEDBACK_HEIGHT);
				feedback->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR22"), FEEDBACKTEXT, COLOR_RED, COLOR_WHITE);
				feedback->addComponent<CallbackDelayer>([&]() { feedback->setAlive(false); }, 2000);
			}
		}, IS_EXIT_BUTTON_POS , aI);

	interactive = true;

	if (PlayerData::instance()->getInventoryOpen()) {
		activatePopUp();
	}

	PlayerData::instance()->setCardGained(false);
	PlayerData::instance()->setInventoryOpen(false);
}

void InventoryScene::createSymbol(Vector2D _pos, string key, string text, int val) {
	GameObject* symbol = addGameObject();
	symbol->addComponent<Transform>(_pos, VECTOR_ZERO, SYMBOL_DIMENSIONS, SYMBOL_DIMENSIONS);
	symbol->addComponent<Image>(SDLApplication::getTexture(key))->attachToCamera();

	GameObject* stat = addGameObject();
	stat->addComponent<Transform>(_pos + STAT_OFFSET, VECTOR_ZERO, 100, 24);
	stat->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), text)->attachToCamera();

	GameObject* value = addGameObject();
	value->addComponent<Transform>(_pos + STAT_VALUE_OFFSET, VECTOR_ZERO, 50, 24);
	value->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), to_string(val))->attachToCamera();
}

// Crea los paneles en los que se colocan las cartas
void InventoryScene::createPanels() {
	deckPanel = createPanel(DP_POSITION, DP_WIDTH, PANEL_HEIGHT, DECK_PANEL);
	createPanel(OP_POSITION, OP_WIDTH, PANEL_HEIGHT, OBJECTS_PANEL);
	inventoryPanel = createPanel(IP_POSITION, IP_WIDTH, PANEL_HEIGHT, INVENTORY_PANEL);
	createPanel(SP_POSITION, SP_WIDTH, PANEL_HEIGHT, STATS_PANEL);

	deckPanel->removeComponent<Image>();
	inventoryPanel->removeComponent<Image>();
}

GameObject* InventoryScene::createPanel(Vector2D pos, int w, int h, string textureKey) {
	GameObject* panel = addGameObject(_grp_UI);
	panel->addComponent<Transform>(pos, VECTOR_ZERO, w, h);
	panel->addComponent<Image>(SDLApplication::getTexture(textureKey))->attachToCamera();

	return panel;
}

void InventoryScene::createMoneyInfo() {
	//Icono de moneda
	GameObject* coin = addGameObject();
	Vector2D pos = Vector2D(WIN_WIDTH - 100, 15);
	coin->addComponent<Transform>(pos, Vector2D(), 64, 64);
	coin->addComponent<Image>(SDLApplication::getTexture("Coin"))->attachToCamera();

	// Texto con el numero de monedas
	int m = PlayerData::instance()->getMoney();
	GameObject* mon = addGameObject();
	if (m / 100 == 0) {
		if (m / 10 == 0) mon->addComponent<Transform>(Vector2D(WIN_WIDTH - 220, 15), VECTOR_ZERO, 50, 48);
		else mon->addComponent<Transform>(Vector2D(WIN_WIDTH - 245, 15), VECTOR_ZERO, 50, 48);
	}
	else mon->addComponent<Transform>(Vector2D(WIN_WIDTH - 270, 15), VECTOR_ZERO, 50, 48);
	mon->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR46"), to_string(m))->attachToCamera();
}

void InventoryScene::createObjects() {
	auto objs = PlayerData::instance()->getRelics();

	int i = 0;
	for (auto& rel : objs) {
		GameObject* g = addGameObject();
		g->addComponent<Transform>(OBJECTS_POSITIONS[i], VECTOR_ZERO, OBJECTS_DIMENSIONS, OBJECTS_DIMENSIONS);
		g->addComponent<Image>(rel->texture)->attachToCamera();
		g->addComponent<PopupComponent>(rel);
		++i;
	}
}

// Se encarga de crear las imagenes de las cartas en el inventario con sus cantidades
void InventoryScene::createCards() {
	int row = 0;
	int column = 0;
	int deckColumn = 0;
	int deckRow = 0;

	Button* startCard = nullptr;
	for (auto& crd : inventory) {
		Vector2D pos = Vector2D(20 + (ALB_CARD_W + 20) * column, 10 + ((ALB_CARD_H + 20) * (1-row)));
		Button* cardButton = createCard(pos, crd.second.card, false);
		if (column == 0) startCard = cardButton;

		if (crd.second.cuantityDeck > 0) {
			createDeckCards(crd.second.card, deckColumn, deckRow);
			deckColumn++;
			if (deckColumn > 5)
			{
				deckColumn = 0;
				deckRow++;
			}
		}
		
		column++;
		if (column > 5)
		{
			column = 0;
			row++;
		}
	}
	if (startCard != nullptr) startCard->setAsDefaultButton();
}
// Se encarga de crear las imagenes de las cartas en la zona del deck
void InventoryScene::createDeckCards(CardId crd, int column, int row) {
	Vector2D posD = Vector2D(20 + (ALB_CARD_W + 20)*column, DECK_HEIGHT - 30 + ((ALB_CARD_H + 20) * row));
	createCard(posD, crd, true);
}
// Se encarga de crear el objeto de la carta, así como sus botones y le añaden la funcionalidad para quitar o poner en el deck
Button* InventoryScene::createCard(Vector2D pos, CardId crd, bool dck) {
	CardData const& cardDt = cardsData().get(Card::getCardIDfromEnum(crd));

	// Imagen de la carta
	GameObject* cardObj = addGameObject();
	cardObj->addComponent<Transform>(pos, VECTOR_ZERO, ALB_CARD_W, ALB_CARD_H);
	cardObj->addComponent<Image>(cardDt.texture);
	// Botón de la carta con su función 
	Button* b = addGameObject<Button>([&, deck = dck, card = crd]()
		{
			InventoryInfo& invCard = inventory.find(Card::getCardIDfromEnum(card))->second;
			// Si se dice que es deck y en el deck hay alguna carta de ese tipo o si se dice que no es deck y hay en deck menos que el total disponible
			if (deck? invCard.cuantityDeck > 0 : invCard.cuantityDeck < invCard.cuantity) {
				// Si era el botón en el deck reduce su cantidad
				if (deck) {
					--invCard.cuantityDeck;
					cardsInDeck--;
					// Si se borra por completo del deck este se reorganiza
					if (invCard.cuantityDeck == 0) {
						reloadDeckCards();
					}
					invCard.myText->changeText(to_string(invCard.cuantity - invCard.cuantityDeck) + "/" + to_string(invCard.cuantity));
					invCard.myDeckText->changeText(to_string(invCard.cuantityDeck) + "/" + to_string(invCard.cuantity));

					TelemetryTracker::instance()->addEvent(EventType::MOVED_FROM_HAND);
				}
				// Si era el botón fuera del deck se aumente su cantidad en este
				else {
					if (cardsInDeck < MAX_CARDS) {
						invCard.cuantityDeck++;
						cardsInDeck++;
						// Si se añade por primera vez al deck este se reorganiza
						if (invCard.cuantityDeck == 1) {
							reloadDeckCards();
						}
						invCard.myText->changeText(to_string(invCard.cuantity - invCard.cuantityDeck) + "/" + to_string(invCard.cuantity));
						invCard.myDeckText->changeText(to_string(invCard.cuantityDeck) + "/" + to_string(invCard.cuantity));
						
						TelemetryTracker::instance()->addEvent(EventType::MOVED_TO_HAND);
					}
				}

				
			}
		}
		, pos, AnimatorInfo("CardSelection", ALB_CARD_W, ALB_CARD_H, cardDt.texture->width(), cardDt.texture->height(), 1, 4),
			-1, nullptr, 0.5f, 0.5f); 
	b->getComponent<ButtonComponent>()->setOnSelected(
		[&](Transform* myTr) {
			if (myTr->getY() > ALB_CARD_H * 2) camTr->setY(-myTr->getY() + ALB_CARD_H * 2);
			else if (myTr->getY() < 0) camTr->setY(myTr->getY() + 10 + (ALB_CARD_H + 20) * 2);
			else camTr->setY(0);
		});
	
	Animator* a = b->getComponent<Animator>();
	a->createAnim(ONOUT, UNSELECTED_CARD_ANIM);
	a->createAnim(ONOVER, SELECTED_CARD_ANIM);
	a->createAnim(ONCLICK, CLICKED_CARD_ANIM);
	a->play(ONOUT);
	a->dettachFromCamera();

	// Texto que indica cuantas cartas hay en el deck
	GameObject* textFrame = addGameObject();
	GameObject* text = addGameObject();
	InventoryInfo& invCard = inventory.find(Card::getCardIDfromEnum(crd))->second;
	Transform* tr = text->addComponent<Transform>(Vector2D (pos.getX() + ALB_CARD_W - 20, pos.getY()), VECTOR_ZERO, 70, 48);
	(dck ? invCard.myDeckText : invCard.myText) = text->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR16"),  to_string(dck ? invCard.cuantityDeck : invCard.cuantity - invCard.cuantityDeck) + "/" + to_string(invCard.cuantity));
	textFrame->addComponent<Transform>(tr->getPos() - Vector2D(3, 7), VECTOR_ZERO, tr->getWidth() + 5, tr->getWidth() + 5);
	textFrame->addComponent<Image>(SDLApplication::getTexture("CardCircle"));

	// Guardar transform y obtener datos de la carta
	Transform* trAux = b->getComponent<Transform>();
	CardData card = cardsData().get(Card::getCardIDfromEnum(crd));

	if (dck) {
		deckButtons[crd].deckButton = b;
		deckButtons[crd].deckImage = cardObj;
		deckButtons[crd].deckText = text;
		deckButtons[crd].deckTextFrame = textFrame;

		deckButtons[crd].ammo.first = addGameObject();
		deckButtons[crd].ammo.second = addGameObject();
		deckButtons[crd].mana.first = addGameObject();
		deckButtons[crd].mana.second = addGameObject();

		Vector2D decsPos = Vector2D(trAux->getPos().getX() + 10, trAux->getPos().getY() + 12);
		createNumber(deckButtons[crd].ammo.first, decsPos, card.maxUses / 10, 'a');
		createNumber(deckButtons[crd].ammo.second, decsPos + Vector2D(10, 0), card.maxUses % 10, 'a');
		createNumber(deckButtons[crd].mana.first, decsPos + Vector2D(4, 32), card.mana / 10, 'm');
		createNumber(deckButtons[crd].mana.second, decsPos + Vector2D(14, 32), card.mana % 10, 'm');
	}
	else {
		invCard.ammo.first = addGameObject();
		invCard.ammo.second = addGameObject();
		invCard.mana.first = addGameObject();
		invCard.mana.second = addGameObject();

		Vector2D decsPos = Vector2D(trAux->getPos().getX() + 10, trAux->getPos().getY() + 12);
		createNumber(invCard.ammo.first, decsPos, card.maxUses / 10, 'a');
		createNumber(invCard.ammo.second, decsPos + Vector2D(10, 0), card.maxUses % 10, 'a');
		createNumber(invCard.mana.first, decsPos + Vector2D(4, 32), card.mana / 10, 'm');
		createNumber(invCard.mana.second, decsPos + Vector2D(14, 32), card.mana % 10, 'm');
	}

	return b;
}

InventoryScene::~InventoryScene() {
	vector<CardId> newDeck;
	for (auto& crd : inventory) {
		for (int i = 0; i < crd.second.cuantityDeck; i++) {
			newDeck.push_back(crd.second.card);
		}
	}

	PlayerData::instance()->setDeck(newDeck);

	TelemetryTracker::instance()->addEvent(EventType::INVENTORY_LEFT, newDeck);
}


void InventoryScene::handleInput() {
	if (interactive) {
		GameState::handleInput();
		if (gmCtrl_.goBack()) {
			if (exitButton->isCurrentButton()) butNavigator->selectDefaultButton();
			else exitButton->setAsCurrentButton();
		}
		// Scroll
		camTr->setY(camTr->getY() - 20 * gmCtrl_.scroll(false));
		if (camTr->getY() > (30 + ((ALB_CARD_H + 20)))) camTr->setY(30 + ((ALB_CARD_H + 20)));
		else if (camTr->getY() <  - ((ALB_CARD_H + 40) * 2)) camTr->setY(-((ALB_CARD_H + 40) * 2));
	}
	else {
		pointer->handleInput();
		button->handleInput();
	}
}

void InventoryScene::reloadDeckCards() {

	for (auto obj : deckButtons) {
		obj.second.deckButton->setAlive(false);
		obj.second.deckImage->setAlive(false);
		obj.second.deckText->setAlive(false);
		obj.second.deckTextFrame->setAlive(false);
		obj.second.ammo.first->setAlive(false);
		obj.second.ammo.second->setAlive(false);
		obj.second.mana.first->setAlive(false);
		obj.second.mana.second->setAlive(false);
	}

	int column = 0;
	int row = 0;
	for (auto& crd : inventory) {
		if (crd.second.cuantityDeck > 0) {
			createDeckCards(crd.second.card, column, row);
			column++;
			if (column > 5)
			{
				column = 0;
				row++;
			}
		}
	}
}

void InventoryScene::update() {
	if (interactive) {
		GameState::update();

		// Posición del ratón
		int x; int y;
		SDL_GetMouseState(&x, &y);

		// Si me encuentro dentro de la zona del inventario
		if (x >= 0 && x <= 942 && y >= 0 && y <= 246) {
			// Desactivo el componente del mazo y añado el del inventario si no existe ya
			if (!inventoryPanel->hasComponent<Image>()) {
				inventoryPanel->addComponent<Image>(SDLApplication::getTexture("InventoryPanel"))->attachToCamera();
				deckPanel->removeComponent<Image>();
			}
		}
		// Si me encuentro dentro de la zona del mazo
		else if (x >= 0 && x <= 942 && y > 246 && y <= 720) {
			// Desactivo el componente del inventario y añado el del mazo si no existe ya
			if (!deckPanel->hasComponent<Image>()) {
				deckPanel->addComponent<Image>(SDLApplication::getTexture("DeckPanel"))->attachToCamera();
				inventoryPanel->removeComponent<Image>();
			}
		}
		// Si me encuentro fuera, desactivo todo
		else {
			if (inventoryPanel->hasComponent<Image>()) inventoryPanel->removeComponent<Image>();
			if (deckPanel->hasComponent<Image>()) deckPanel->removeComponent<Image>();
		}
	}

	else {
		pointer->update();
		screen->update();
		tuto->update();
		text1->update();
		text2->update();
		button->update();
	}
}

// Crear un número según los datos recibidos
void InventoryScene::createNumber(GameObject* number, Vector2D pos, int value, char type) {
	// Añadir componentes (transform y animator)
	number->addComponent<Transform>(pos, Vector2D(), UI_AMMO_NUMBERS_WIDTH - 1, UI_AMMO_NUMBERS_HEIGHT - 1);

	// Seleccionar textura
	Texture* txt;
	if (type == 'a') txt = SDLApplication::getTexture(STATISTICS_NUMBERS);
	else txt = SDLApplication::getTexture(CARDS_NUMBERS);

	// Añadir animator y crear animaciones
	auto anim = number->addComponent<Animator>(txt, CARDS_NUMBERS_WIDTH, CARDS_NUMBERS_HEIGHT, CARDS_NUMBERS_ROWS, CARDS_NUMBERS_COLUMNS);
	for (int j = 0; j < N_NUMBERS - 2; j++) anim->createAnim(to_string(j), j, j, 1, 0);

	// Reproducir animación correspondiente
	anim->play(to_string(value));
}

void InventoryScene::activatePopUp() {
	interactive = false;

	// Objeto que cubre la pantalla
	screen = addGameObject(_grp_UI);
	screen->addComponent<Transform>(Vector2D(), VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	screen->addComponent<Image>(&sdlutils().images().at(DARK_PLAIN_TEXTURE))->attachToCamera();

	// Imagen de tuto (cambiar luego t->width por constantes)
	tuto = addGameObject(_grp_UI);
	tuto->addComponent<Transform>(TUTO_POPUP_POS, Vector2D(), TUTO_POPUP_WIDTH, TUTO_POPUP_HEIGHT);
	Animator* anim = tuto->addComponent<Animator>(SDLApplication::getTexture(TUTO_TALKING_TEXTURE),
		TUTO_POPUP_SPRITE_WIDTH, TUTO_POPUP_SPRITE_HEIGHT, 2, 1);
	anim->attachToCamera();
	anim->createAnim("idle", 0, 1, 3, -1);
	anim->play("idle");

	// Mostar texto correspondiente
	// Color del texto
	SDL_Color color = { 213, 180, 152 };
	Transform* tr = nullptr;

	// Añadir objeto con el componente transform y el de texto con el string adecuado
	text1 = addGameObject(_grp_UI);
	text2 = addGameObject(_grp_UI);

	// Seleccionar texto
	// Primer texto
	tr = text1->addComponent<Transform>(TUTO_POPUP_POS + TEXT_OFFSET, VECTOR_ZERO, TUTO_POPUP_WIDTH - 120, TUTO_POPUP_HEIGHT - 120);
	text1->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_REG30), texts[0], color, true)->attachToCamera();

	// Segundo texto
	text2->addComponent<Transform>(Vector2D(tr->getPos().getX(), tr->getPos().getY() + tr->getHeight()), VECTOR_ZERO, TUTO_POPUP_WIDTH - 120, TUTO_POPUP_HEIGHT - 120);
	text2->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_REG30), texts[1] + texts[2], color, true)->attachToCamera();

	// Boton
	AnimatorInfo aI = AnimatorInfo(RESUME);
	button = addGameObject<Button>(_grp_UI, [&]() { deactivatePopUp(); }, RESUME_BUTTON_POS, aI);
	button->getComponent<Animator>()->attachToCamera();
	button->setAsCurrentButton();
}

void InventoryScene::deactivatePopUp() {
	interactive = true;
	screen->setAlive(false);
	tuto->setAlive(false);
	text1->setAlive(false);
	text2->setAlive(false);
	button->setAlive(false);

	screen = tuto = text1 = text2 = button = nullptr;
}