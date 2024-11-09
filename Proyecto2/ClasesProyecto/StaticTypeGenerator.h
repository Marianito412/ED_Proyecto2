#pragma once
#include "OpPartGenerator.h"

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
