#pragma once
#include "Operation.h"
#include "OpPartGenerator.h"
#include "../Estructuras/Abstractas/Dictionary.h"
#include "../Estructuras/Abstractas/List.h"
#include "../Estructuras/Concretas/ArrayList.h"

class OpGenerator
{
public:
    List<Operation>* Ops;
    Dictionary<int, int>* Dict;
    int Amount;
    OpPartGenerator* TypeGenerator;
    OpPartGenerator* KeyGenerator;

    OpGenerator()
    {
        this->Dict = nullptr;
        Amount = 100;
        Ops = new ArrayList<Operation>(Amount);
        TypeGenerator = nullptr;
        KeyGenerator = nullptr;
    }
    OpGenerator(Dictionary<int, int>* Dict, int amount, OpPartGenerator* TypeGen, OpPartGenerator* KeyGen)
    {
        this->Dict = Dict;
        Amount = amount;
        Ops = new ArrayList<Operation>(amount);
        TypeGenerator = TypeGen;
        KeyGenerator = KeyGen;
    }
    ~OpGenerator()
    {
        delete Ops;
        delete TypeGenerator;
        delete KeyGenerator;
    }

    void Generate()
    {
        Ops->clear();
        for(int i = 0; i<Amount; i++)
        {
            Operation NewOp = Operation();
            TypeGenerator->Next(&NewOp, Dict);
            KeyGenerator->Next(&NewOp, Dict);
            Ops->append(NewOp);
        }
    }
    List<Operation>* GetOps()
    {
        return Ops;
    }
};
