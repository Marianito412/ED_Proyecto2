#pragma once
#include "OpPartGenerator.h"

class RandomKeyGenerator : public OpPartGenerator
{
public:
    void Next(Operation* Op, Dictionary<int, int>* Dict)
    {
        if (Op->Op == OpType::Insert || Op->Op == OpType::Find)
        {
            Op->Key = rand()%40000;
        }
        if (Op->Op == OpType::Remove)
        {
            int Key;
            do
            {
                Key = rand()%40000;
            }while (Dict->contains(Key));
            Op->Key = Key;
        }
    }
};
