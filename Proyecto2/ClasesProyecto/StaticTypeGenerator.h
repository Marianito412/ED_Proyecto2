#pragma once
#include "OpPartGenerator.h"

/*
 * Autor: Mariano Soto
 * Este generador crea tipos de operaciones de un único tipo definido en el constructor
 */

class StaticTypeGenerator : public OpPartGenerator
{
public:
    OpType Type;

    StaticTypeGenerator(OpType Type)
    {
        this->Type = Type;
    }

    void Next(Operation* Op, Dictionary<int, int>* Dict)
    {
        Op->Op = Type;
    }
};
