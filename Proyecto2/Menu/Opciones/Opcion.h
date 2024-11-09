﻿#pragma once
#include <string>
#include <iostream>

using std::ostream;

/*
 * Autor: Mariano Soto
 * Opcion: Clase abstracta utilizada por menu, contiene una función Ejecutar() que Menu llama.
 * Las subclases sobreescriben esta función para implementar su comportamiento
 */

template <typename E>
class Opcion
{
public:
    std::string Nombre;
    virtual void Ejecutar(E* Objeto) = 0;
};

template <typename E>
inline ostream& operator <<(ostream& os, const Opcion<E>& opcion) {
    os << "(" << opcion.Nombre << ")";
    return os;
}