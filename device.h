//
// Created by Oscar Gao on 10/11/21.
//

#ifndef P16140_DEVICE_H
#define P16140_DEVICE_H
#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

// define a class of devices
class device {
public:
    explicit device(const vector<string>& comp);
    void printDevice() const; // print information of device
    int logic (int input1, int input2) const; // logic of the gate

    string type; // type of gate
    string i1; // input 1
    string i2; // input 2, set to "" for 1 input gates
    string out; // output
};

#endif //P16140_DEVICE_H
