//
// Created by Oscar Gao on 10/11/21.
//

#include "device.h"

// device constructor
device::device(const vector<string>& comp)
{
    this->type = comp[0];
    if (comp.size() == 3) // INV and BUF
    {
        this->i1 = comp[1];
        this->i2 = "";
        this->out = comp[2];
    }
    else if (comp.size() == 4) // all other gates
    {
        this->i1 = comp[1];
        this->i2 = comp[2];
        this->out = comp[3];
    }
    else
    {
        throw invalid_argument("ERROR INITIALIZING DEVICE!!");
    }
}

void device::printDevice() const
{
    cout << "type: " << this->type << ", ";
    cout << "i1: " << this->i1 << ", ";
    cout << "i2: " << this->i2 << ", ";
    cout << "out: " << this->out << endl;
}

int device:: logic(int input1, int input2 = 0) const
{
    int output;
    if (this->type == "INV")
    {
        output = !input1;
    }
    else if (this->type == "BUF")
    {
        output = input1;
    }
    else if (this->type == "AND")
    {
        output = input1&input2;
    }
    else if (this->type == "NAND")
    {
        output = !(input1&input2);
    }
    else if (this->type == "OR")
    {
        output = input1|input2;
    }
    else if (this->type == "NOR")
    {
        output = !(input1|input2);
    }
    else
    {
        output = 2;
        throw invalid_argument("ERROR!! INVALID TYPE RAISE ERROR WHEN COMPUTING LOGIC!!");
    }
    return output;
}