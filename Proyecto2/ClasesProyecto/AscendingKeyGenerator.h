#pragma once
#include "OpPartGenerator.h"
/*
    Autor: Steven David Loaíciga Segura
    Recibe: Operation Type, que es una enumeraci�n de las distintas opciones que se pueden realizar en el diccionario. Y el diccionario.
    Funcion: Tiene 1 atributo:
        1- i: es el número de iteraciones de inserciones y borrados.
    Esto va a generar una key válida según el caso en el que se usen Keys por Ascendencia.
*/
class AscendingKeyGenerator : public OpPartGenerator
{
public:
    int i = 1;
    void Reset() {
        i = 1;
    }
	void Next(Operation* Op, Dictionary<int, int>* Dict) {

        if (Op->Op == OpType::Insert || Op->Op == OpType::Find)
        {
            Op->Key = i;
            i++;
        }

            if (Op->Op == OpType::Remove)
            {
                while (!Dict->contains(i)) {
                    i++;
                }
                Op->Key = i;
            }
		}
	
};