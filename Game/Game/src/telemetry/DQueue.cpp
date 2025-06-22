#include "DQueue.h"
#include "events/GenericEvent.h"

// Constructor
template <typename T, size_t SIZE>
DQueue<T, SIZE>::DQueue() : items{} {
    frontP = -1;
    rearP = -1;
}

// Verificar si la cola está llena
template <typename T, size_t SIZE>
bool DQueue<T, SIZE>::isFull() {
    if (frontP == 0 && rearP == SIZE - 1) {
        return true;
    }
    if (frontP == (rearP + 1) % SIZE) {
        return true;
    }
    return false;
}

// Verificar si la cola está vacía
template <typename T, size_t SIZE>
bool DQueue<T, SIZE>::isEmpty() {
    return frontP == -1;
}

// Insertar un elemento
template <typename T, size_t SIZE>
void DQueue<T, SIZE>::enQueue(T& element) {
    if(!isFull()) {
        if (frontP == -1) {
            frontP = 0;  // Si la cola está vacía, colocamos el primer elemento en la posición 0
        }
        rearP = (rearP + 1) % SIZE;  // La cola es circular
        items[rearP] = element;     // Insertamos el elemento
    }
}

// Eliminar un elemento
//template <typename T, size_t SIZE>
//T DQueue<T, SIZE>::deQueue() {
//    if (isEmpty()) {
//        return nullptr;
//    }
//    else {
//        T element = items[frontP];
//        if (frontP == rearP) {
//            // Si solo hay un elemento en la cola, reiniciamos
//            frontP = -1;
//            rearP = -1;
//        }
//        else {
//            frontP = (frontP + 1) % SIZE;  // Actualizamos el índice de frontP para hacer la cola circular
//        }
//        return element;
//    }
//}
template <typename T, size_t SIZE>
void DQueue<T, SIZE>::deQueue() {
    if(!isEmpty()) {
        items[frontP] = nullptr;
        if (frontP == rearP) {
            // Si solo hay un elemento en la cola, reiniciamos
            frontP = -1;
            rearP = -1;
        }
        else {
            frontP = (frontP + 1) % SIZE;  // Actualizamos el índice de frontP para hacer la cola circular
        }
    }
}

// Mostrar los elementos de la cola
template <typename T, size_t SIZE>
void DQueue<T, SIZE>::display() {
    if (isEmpty()) {
        return;
    }
    cout << "Front -> " << frontP << endl;
    cout << "Items -> ";
    for (int i = frontP; i != rearP; i = (i + 1) % SIZE) {
        cout << items[i] << "\t";
    }
    cout << items[rearP] << endl;  // Mostrar el último elemento
    cout << "Rear -> " << rearP << endl;
}

// Método para obtener el tamaño de la cola
template <typename T, size_t SIZE>
size_t DQueue<T, SIZE>::size() {
    if (isEmpty()) {
        return 0;
    }
    else if (frontP <= rearP) {
        return rearP - frontP + 1;  // La cola no ha dado la vuelta
    }
    else {
        return SIZE - frontP + rearP + 1;  // La cola ha dado la vuelta
    }
}

// Método para obtener el primer elemento de la cola
template <typename T, size_t SIZE>
T DQueue<T, SIZE>::front() {
    if (isEmpty()) {
        return nullptr;
    }
    return items[frontP];  // Devuelve el primer elemento
}

template class DQueue<GenericEvent*, 500>;  // Instancia de la plantilla para puntero a GenericEvent y tamaño 500

