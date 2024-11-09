﻿#pragma once
#include "OpPartGenerator.h"

class RandomTypeGenerator : public OpPartGenerator
{
public:
    void Next(Operation* Op, Dictionary<int, int>* Dict)
    {
        int RandOp =  rand()%3;
        if (RandOp == 0)
        {
            Op->Op = OpType::Insert;
        }
        if (RandOp == 1)
        {
            Op->Op = OpType::Remove;
        }
        if (RandOp == 2)
        {
            Op->Op = OpType::Find;
        }
    }
};