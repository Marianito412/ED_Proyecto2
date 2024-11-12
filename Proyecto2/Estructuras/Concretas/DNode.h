#pragma once
/*
* Clase del nodo doblemente enlazado, tiene dos constructores
* Escrito por el profesor
*/
template <typename E>
class DNode {
public:
	E element;
	DNode<E>* next;
	DNode<E>* previous;

	DNode(E element, DNode<E>* next, DNode<E>* previous)  {
		this->element = element;
		this->next = next;
		this->previous = previous;
	}
	DNode(DNode<E>* next, DNode<E>* previous) {
		this->next = next;
		this->previous = previous;
	}
};

