//
// Created by Oscar Gao on 10/11/21.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "device.h"

using namespace std;

int main()
{
    // ask the filename and read in the circuit file
    string filename;
    cout << "Please Specify the Circuit:" << endl;
    cin >> filename;
#ifdef DEBUG
    cout << "vector: " << input_vector << endl;
    for (auto x: input_clean)
    {
        cout << x << " ";
    }
    cout << endl;
#endif
    // get the circuit file into a c++ vector
    ifstream file(filename);
    vector <string> file_contents;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (!line.empty() && line.find_first_not_of(' ') != std::string::npos)
            { // check for empty line and all white space line
                file_contents.push_back(line);
            }
        }
    }
    // further, unpack into components (into 2D vector)
    int lineNum = 0; // number of valid lines
    vector< vector<string> > comp (file_contents.size());
    for (int i=0; i<file_contents.size(); i++)
    {
        istringstream ss(file_contents[i]);
        string word;
        while (ss >> word)
        {
            comp[i].push_back(word);
            if (word == "OUTPUT") // the word "OUTPUT" denotes the last valid line
            {
                lineNum = i;
//                cout << lineNum << endl;
            }
        }
    }
    // turn input into circuit here
    vector<string> inputs; // vector to hold all inputs ports
    vector<string> outputs; // vector to hold all output ports
    vector<device> device_list; // vector with a list of all devices (device class)
    for (int i = 0; i<= lineNum; i++)
    {
        // keep record of all input ports
        if ((comp[i][0]) == "INPUT")
        {
            int pointer1 = 1;
            while (comp[i][pointer1] != "-1")
            {
                inputs.push_back(comp[i][pointer1]);
                pointer1++;
            }
        }
        else if ((comp[i][0]) == "OUTPUT") // keep record of all output ports
        {
            int pointer2 = 1;
            while (comp[i][pointer2] != "-1")
            {
                outputs.push_back(comp[i][pointer2]);
                pointer2++;
            }
        }
        else if ((comp[i][0]) == "INV" || (comp[i][0]) == "BUF" || (comp[i][0]) == "NOR" || (comp[i][0]) == "OR" ||
        (comp[i][0]) == "AND" || (comp[i][0]) == "NAND") // keep record of circuit devices
        {
            device_list.emplace_back(device(comp[i]));
//            device_list[i].printDevice(); // print out device's information
        }
        else
        {
            string message = "ERROR!!! INVALID LINE IN CIRCUIT FILE!!: " + file_contents[i];
            throw invalid_argument(message);
            break;
        }
    }
#ifdef DEBUG
    for (auto const &pair: inputs) {
        std::cout << "{" << pair.first << ": " << pair.second << "}";
    }
#endif
    // ask the user to input test vector
    string input_vector;
    cout << "Please Input Test Vector of Size " << inputs.size() << endl;
    cin >> input_vector;
    vector<int> input_clean;
    // check if user's input vector has the correct length
    if (input_vector.length() != inputs.size())
    {
        cout << "Input Vector Not Correct Length." << endl;
        return 0;
    }
    // check if it is a binary vector input: only has 0 and 1
    for (auto a_char: input_vector)
    {
        if ((a_char != '0') && (a_char != '1'))
        {
            cout << "Please Input a Binary Vector! Try Again!" << endl;
            return 0;
        }
        else
        { // clean up the input vector to be 0 or 1
            for (auto x: input_vector) {
                input_clean.push_back(x - '0');
            }
        }
    }

    unordered_map<string, int> netValues; // map to hold values of nets

    // log the input vector values into the net value
    for (int i=0; i<inputs.size(); i++)
    {
        netValues[inputs[i]] = input_clean[i];
    }

    // run the simulation now
    bool finished = false;
    while(!finished)
    {
        for (const auto& a_device: device_list)
        { // run if there is a valid key in map for the gates' input
            // if ran, put output value in map
            if ((a_device.type == "BUF" || a_device.type == "INV") && netValues.find(a_device.i1) != netValues.end())
            {
                int output = a_device.logic(netValues[a_device.i1], 0);
                netValues[a_device.out] = output;
            }
            else if (netValues.find(a_device.i1) != netValues.end() && netValues.find(a_device.i2) != netValues.end())
            {
                int output = a_device.logic(netValues[a_device.i1], netValues[a_device.i2]);
                netValues[a_device.out] = output;
            }
        }
        // check if finished
        finished = true;
        for (auto &out_port: outputs)
        { // simulation finishes only when all ports in the output array has a valid key in map
            if (netValues.find(out_port) == netValues.end())
            {
                finished = false;
                break;
            }
        }
    } // end simulation loop
#ifdef DEBUG
    for (auto const &pair: inputs) {
            std::cout << "{" << pair.first << ": " << pair.second << "}";
        }
        cout << endl;
#endif
    // print out the output
    cout << "Output Vector: ";
    for (auto &a_output: outputs)
    {
        cout << netValues[a_output];
    }
    cout << endl;
    return 0;
}