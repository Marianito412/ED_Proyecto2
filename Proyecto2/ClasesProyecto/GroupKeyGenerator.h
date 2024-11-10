#pragma once
#include "OpPartGenerator.h"
#include "../Estructuras/Abstractas/Dictionary.h"

/*  
    Autor: Javier Vega Abarca
    Recibe: Operation Type, que es una enumeración de las distintas opciones que se pueden realizar en el diccionario. Y el diccionario.
    Funcion: Tiene 2 atributos:
        1- tamanno: es el tamaño de los grupos para ir iterando, se genera de manera random
        2- actual: se genera un numero aleatorio y luego se va iterando sobre él la cantidad de veces que tamanno diga.
    Ésto va a generar una key válida según el caso en el que se usen Keys por Grupos.
*/

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