#pragma once
#include "OpPartGenerator.h"
#include "../Estructuras/Abstractas/Dictionary.h"

/*  
    Autor: Javier Vega Abarca
    Recibe: Operation Type, que es una enumeraci�n de las distintas opciones que se pueden realizar en el diccionario. Y el diccionario.
    Funcion: Tiene 2 atributos:
        1- tamanno: es el tama�o de los grupos para ir iterando, se genera de manera random
        2- actual: se genera un numero aleatorio y luego se va iterando sobre �l la cantidad de veces que tamanno diga.
    �sto va a generar una key v�lida seg�n el caso en el que se usen Keys por Grupos.
*/

class GroupKeyGenerator : public OpPartGenerator
{
public:
    int tamanno;
    int actual;
    void Reset()
    {
        tamanno = 0;
        actual = 0;
    }
    void Next(Operation* Op, Dictionary<int, int>* Dict)
    {
        if (Op->Op == OpType::Insert || Op->Op == OpType::Find) {
            if (tamanno == 0) { 
                tamanno = 10 + rand() % 40; 
                actual += rand() % 400; 
            }
            Op->Key = actual;
            actual++;
            tamanno--;
        }
        if (Op->Op == OpType::Remove) {
            int Key;
            do
            {
                if (tamanno == 0) { 
                    tamanno = 10 + rand() % 40; 
                    actual += rand() % 400; 
                }
                Op->Key = actual;
                actual++;
                tamanno--;
            } while (Dict->contains(Key));
            Op->Key = Key;
        }
    }
};