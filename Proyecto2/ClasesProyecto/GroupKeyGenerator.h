#pragma once
#include "OpPartGenerator.h"
#include "../Estructuras/Abstractas/Dictionary.h"


class GroupKeyGenerator : public OpPartGenerator
{


public:
    int tamanno;
    int actual;
    
    void Next(Operation* Op, Dictionary<int, int>* Dict)
    {
        if (Op->Op == OpType::Insert || Op->Op == OpType::Find) {
            if (tamanno = 0) { 
                tamanno = rand() % 500; 
                actual += rand() % 400; 
            }
            Op->Key = actual;
            actual++;
            tamanno--;
        }
        if (Op->Op == OpType::Borrado) {
            int Key;
            do
            {
                if (tamanno = 0) {
                    tamanno = rand() % 500;
                    actual += rand() % 400;
                }
                Key = actual;
            } while (Dict->contains(Key));
            Op->Key = Key;
        }
    }
};