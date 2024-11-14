#pragma once
#include "Operation.h"
#include "../Estructuras/Abstractas/Dictionary.h"

/*
 * Autor: Mariano Soto
 * Esta interfaz es la clase base que los generadores de partes necesitaran implemntar para ser usados
 * por el generador
 */
class OpPartGenerator
{
public:
    virtual ~OpPartGenerator() {}
    virtual void Reset(){}
    virtual void Next(Operation* Op, Dictionary<int, int>* Dict) = 0;
};
