#pragma once
#include "OpPartGenerator.h"

/*
 * Autor: Mariano Soto
 * Esta clase genera una llave aleatoria para cualquier tipo de operación.
 * Si la operación es borrado, se asegura que la llave exista en el diccionario
 */

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
