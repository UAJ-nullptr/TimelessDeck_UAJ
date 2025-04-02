#include "ButtonNavigator.h"
//#include <experimental/map>

// Constructora
ButtonNavigator::ButtonNavigator() : gmCtrl_(gmCtrl()), unlockedMovement_(true) {}

// Selecciona el bot�n adjacente al actual en la direcci�n indicada
bool ButtonNavigator::changePos(way w) {
	bool moved = false;
	if (unlockedMovement_) {
		int dir = (w < 2) ? d_x : d_y;
		// incrementa
		if (w % 2 != 0) {
			if (std::next(currentButton.pos[w]) != matrix[dir][currentButton.supPos[w]].end()) {
				++currentButton.pos[w];
				moved = true;
			}
		}
		// decrementa
		else {
			if (currentButton.pos[w] != matrix[dir][currentButton.supPos[w]].begin()) {
				--currentButton.pos[w];
				moved = true;
			}
		}

		setCurrentButton(currentButton.pos[w]->second);
	}
	return moved;
}

// Selecciona el bot�n encima del actual
void ButtonNavigator::up() {
	changePos(u);
}
// Selecciona el bot�n debajo del actual
void ButtonNavigator::down() {
	changePos(d);
}
// Selecciona el bot�n a la derecha del actual
void ButtonNavigator::left() {
	changePos(l);
}
// Selecciona el bot�n a la izquierda del actual
void ButtonNavigator::right() {
	changePos(r);
}

// A�ade un bot�n al sistema de navegaci�n entre estos, recibe su componente Imagen
ButtonData ButtonNavigator::insert(Image* im, float horizontalMult, float verticalMult) {
	SDL_Rect rr = im->getRect();

	ButtonData bd;
	bd.buttonIm = im;

	rr.x /= 12;
	rr.y /= 12;
	rr.w /= 12;
	rr.h /= 12;
	SDL_Rect orr = rr;

	rr.x += (rr.w - rr.w * horizontalMult) / 2;
	rr.y += (rr.h - rr.h * verticalMult) / 2;

	rr.w *= horizontalMult;
	rr.h *= verticalMult;

	
	// area total en el map
	rr.x -= rr.w/2;
	rr.y -= rr.h/2;
	rr.w *= 2;
	rr.h *= 2;

	// sacar los 4 bordes
	int up[2] = { rr.x + rr.w / 2, rr.y };
	int down[2] = { rr.x + rr.w / 2, rr.y + rr.h - 1 };
	int left[2] = { rr.x, rr.y + rr.h / 2 };
	int right[2] = { rr.x + rr.w - 1, rr.y + rr.h / 2 };

	// insertar laterales en el map
	std::pair<button_map::iterator, bool> its[4];
	
	its[u] = insertBorder(d_x, up[d_x], up[d_y], bd, orr);
	bd.supPos[u] = up[d_x];
	its[d] = insertBorder(d_x, down[d_x], down[d_y], bd, orr);
	bd.supPos[d] = down[d_x];
	its[l] = insertBorder(d_y, left[d_x], left[d_y], bd, orr);
	bd.supPos[l] = left[d_y];
	its[r] = insertBorder(d_y, right[d_x], right[d_y], bd, orr);
	bd.supPos[r] = right[d_y];

	// asignar los laterales en el ButtonData
	for (int i = 0; i < 4; ++i) {
		bd.pos[i] = its[i].first;
	}

	// insertar en todo el �rea del bot�n del map
	for (int i = rr.x; i < rr.x + rr.w; ++i) {
		for (int j = rr.y; j < rr.y + rr.h; ++j) {
			if (j >= orr.y && j < orr.y + orr.h) matrix[d_x][i][j] = bd;
			else matrix[d_x][i].insert({ j, bd });
			
			if (i >= orr.x && i < orr.x + orr.w) matrix[d_y][j][i] = bd;
			else matrix[d_y][j].insert({ i, bd });
		}
	}

	// 
	for (int i = 0; i < 4; ++i) {
		if (its[i].second) its[i].first->second = bd;
	}

	return ButtonData(bd);
}

std::pair<ButtonNavigator::button_map::iterator, bool> ButtonNavigator::insertBorder(direction dir, int x, int y, ButtonData bd, SDL_Rect orr) {
	std::pair<button_map::iterator, bool> it;
	if (dir == d_x) it = matrix[dir][x].insert({ y, bd });
	else it = matrix[dir][y].insert({ x, bd });

	if (!it.second) {
		if (dir == d_x && y >= orr.y && y < orr.y + orr.h ||
			dir == d_y && x >= orr.x && x < orr.x + orr.w) {
			it.first->second = bd;
			it.second = true;
		}
	}
	return it;
}

void ButtonNavigator::erase(Image* im) {
	if (im == currentButton.buttonIm) {
		selectDefaultButton();
	}


	//for (int o = 0; o < 2; ++o) {
	//	for (auto& m : matrix[o]) {
	//		std::experimental::erase_if(m.second,
	//			[im](const auto& bd) {
	//				return bd.second.buttonIm == im;
	//			});
	//	}
	//}

	for (int o = 0; o < 2; ++o) {
		for (auto& m : matrix[o]) {
			for (auto it = m.second.begin(); it != m.second.end(); ) {
				if (it->second.buttonIm == im) {
					it = m.second.erase(it); // Eliminar correctamente del map
				}
				else {
					++it;
				}
			}
		}
	}
}

// Recibe un bot�n y lo asigna como el por defecto
void ButtonNavigator::setDefaultButton(ButtonData bd) {
	defaultButton = bd;
	selectDefaultButton();
}
// Recibe un bot�n y lo asigna como el actual
void ButtonNavigator::setCurrentButton(ButtonData bd) {
	currentButton = bd;
}
// Selecciona el bot�n por defecto
void ButtonNavigator::selectDefaultButton() {
	setCurrentButton(defaultButton);
}

// Bloquea la navegacion entre botones
void ButtonNavigator::lockMovement() {
	unlockedMovement_ = false;
}
// Desbloquea la navegaci�n entre botones
void ButtonNavigator::unlockMovement() {
	unlockedMovement_ = true;
}