#pragma once
#include "OpPartGenerator.h"

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