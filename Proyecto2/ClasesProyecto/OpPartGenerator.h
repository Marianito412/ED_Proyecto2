#pragma once
#include "Operation.h"
#include "../Estructuras/Abstractas/Dictionary.h"

class OpPartGenerator
{
public:
    virtual ~OpPartGenerator() {}
    virtual void Reset();
    virtual void Next(Operation* Op, Dictionary<int, int>* Dict) = 0;
};
