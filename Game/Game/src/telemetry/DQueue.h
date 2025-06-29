#pragma once
#include <iostream>

template <typename T, size_t SIZE>
class DQueue {
private:
    T items[SIZE];
    int frontP, rearP;

public:
    DQueue();

    bool isFull();   // Verificar si la cola está llena
    bool isEmpty();  // Verificar si la cola está vacía
    void enQueue(T& element);   // Insertar un elemento
    void deQueue();    // Eliminar un elemento
    void display();   // Mostrar los elementos de la cola
    size_t size();    // Tamaño de la cola
    T front();    // Obtener el primer elemento sin eliminarlo
};
