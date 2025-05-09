#pragma once

#include "Image.h"
#include "../../sdlutils/InputHandler.h"
#include "../../sdlutils/SDLUtils.h"

class TextComponent : public Image {
private:
	Font* font;
	std::string text;
	SDL_Color color, bgColor;
	bool wrapped;
	float originalWidth;
	Texture texture;
	
public:
	// Texto negro sin fondo en una l�nea
	TextComponent(Font* _f, std::string _text);
	// Texto negro sin fondo ajustado a una anchura
	TextComponent(Font* _f, std::string _text, bool _wrapped);
	// Texto con color personalizado sin fondo en una l�nea
	TextComponent(Font* _f, std::string _text, SDL_Color _color);
	// Texto con color personalizado sin fondo ajustado a una anchura
	TextComponent(Font* _f, std::string _text, SDL_Color _color, bool _wrapped);
	// Texto con color personalizado con fondo personalizado
	TextComponent(Font* _f, std::string _text, SDL_Color _color, SDL_Color _bgColor);
	// Texto con color personalizado con fondo personalizado ajustado a una anchura
	TextComponent(Font* _f, std::string _text, SDL_Color _color, SDL_Color _bgColor, bool _wrapped);
	// Ajusta el transform al texto
	virtual void initComponent();

	// Recarga la textura tras actualizaciones
	void reloadTexture();

	// Cambia el texto mostrado
	void changeText(std::string newText);
	// Cambia la fuente
	void changeFont(Font* newFont);
	// Cambia el color, recibe SDL_Color
	void changeColor(SDL_Color newColor);
	// Cambia el color, recibe el color en hexadecimal
	void changeColor(std::string newColorHex);

	// Asigna si el ancho del texto depende del transform o no
	void setWrapped(bool w);
	// Devuelve si el ancho del texto depende del transform o no
	bool isWrapped();

	// A�ade texto al actual
	std::string operator +=(std::string s);

	// Devuelve el texto
	inline string getText() { return text; }
};

