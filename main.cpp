#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "parameters.h"

using namespace std;

std::string trim(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

typedef struct {
    int data;
} asmData;

typedef struct {
    string instructionName;
    asmType instruction;
    int a;
    int b;
} asmInstruction;

int parseStringAsInt(string stringToParse)
{
    string::size_type size;
    int integerValue;

    if (stringToParse.find("0x") != string::npos) {
        // this stringToParse is in hex, strip off the first 2 chars which should be 0x
        integerValue = stoi(&stringToParse[2], nullptr, 16);
    } else if (stringToParse.find("$") != string::npos) {
        // this stringToParse is a register, strip off the first char which should be a $
        integerValue = stoi(&stringToParse[1], &size);
    } else {
        try {
            // treat this stringToParse as a number, parse as is
            integerValue = stoi(stringToParse, &size);
        }
        catch(invalid_argument e) {
            cerr << "Exception! String: " << stringToParse << " was not a valid hex value, register value, or integer value";
            exit(1);
        }
    }

    return integerValue;
}

int main(int argc, char *argv[])
{
    map<string, asmType> asmCollection = initAsmCollection();
    vector<asmInstruction> programInstructions;
    vector<asmData> programData;

    ifstream infile(argv[1]);

    if (infile.good()) {

        stringstream iss;
        string section;
        string line;

        while (getline(infile, line)) {

            line = trim(line);


            if ((line[0] == '/') && (line[1] == '/')) {
                // ignore comments that start the line
                continue;
            }
            else {
                // this line is not a comment, lets continue

                iss << line;
                string token;
                while (getline(iss, token, ' ')) {

                    token = trim(token);

                    if (!token.empty()) {
                        cout << "|" << token << "|";
                        if (token[0] == '.') {
                            // if token starts with a . then we are changing sections
                            section = token.substr(1);
                        }
                        else if ((token[0] == '/') && (token[1] == '/')) {
                            // if the token is // then we are done with this line, go to the next line
                            // we do this by clearing the stringstream (a.k.a setting it equal to an empty string)
                            iss.str(std::string());
                        }
                        else {
                            if(section == "data") {
                                int data = parseStringAsInt(token);
                                asmData curData = (asmData) {
                                        .data = data
                                };
                                programData.push_back(curData);
                            }
                            else {
                                if (asmCollection.find(token) != asmCollection.end()) {
                                    string curInstructionName = token;
                                    // get argument A skipping any empty space
                                    getline(iss, token, ' ');
                                    while(token.empty() && getline(iss, token, ' '));
                                    int intArgumentA = parseStringAsInt(token);

                                    asmInstruction curInstruction = (asmInstruction) {
                                            .instruction     = asmCollection[curInstructionName],
                                            .instructionName = curInstructionName,
                                            .a               = intArgumentA
                                    };

                                    if(asmCollection[curInstructionName].arguments == 2) {
                                        // get argument B
                                        getline(iss, token, ' ');
                                        while(token.empty() && getline(iss, token, ' '));
                                        int intArgumentB = parseStringAsInt(token);

                                        // then add the second argument to the instruction
                                        curInstruction.b = intArgumentB;
                                    }

                                    programInstructions.push_back(curInstruction);
                                }
                                else {
                                    throw invalid_argument("Invalid assembly instruction found: "+token);
                                }
                            }
                        }

                        cout << endl;
                    }
                }

                iss.clear();
            }
        }

    } else {
        cout << "File does not exist" << endl;
    }

    infile.close();

    return 0;
}
