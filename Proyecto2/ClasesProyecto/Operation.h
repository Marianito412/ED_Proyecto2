#pragma once
#include <iostream>

enum OpType
{
    Insert = 0,
    Remove = 1,
    Find = 2
};

/*
 * Autor: Mariano Soto
 * Esta clase es únicamente utilizada para describir una operación a realizar sobre un diccionario
 * Describe el tipo de operación y la llave sobre la cual realizar la operación
 */
class Operation
{
public:
    OpType Op;
    int Key;
    
    Operation()
    {
        Op = OpType::Insert;
        Key = 0;
    }
    Operation(OpType op, int key)
    {
        Op = op;
        Key = key;
    }
};

inline std::ostream& operator <<(std::ostream& os, const Operation Op) {
    os << "(" << Op.Op<< ", " << Op.Key << ")";
    return os;
}