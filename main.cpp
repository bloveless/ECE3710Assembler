#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <stdexcept>
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
    string data;
} asmData;

typedef struct {
    string instructionName;
    asmType instruction;
    int a;
    int b;
    string aText;
    string bText;
    string aLabel;
    string bLabel;
    string lineLabel;
} asmInstruction;

asmInstruction parseStringAsArgument(asmInstruction &curInstruction, string stringToParse) {
    int integerValue;
    int foundLabel = 0;

    if (stringToParse.find("0x") != string::npos) {
        // this stringToParse is in hex, strip off the first 2 chars which should be 0x
        string subString = stringToParse.substr(2, string::npos);

        // let the stream parser parse the hex value
        stringstream tmpString;
        tmpString << std::hex << subString;

        // and store it back into the integer
        tmpString >> integerValue;
    } else if (stringToParse.find("$") != string::npos) {
        // this stringToParse is a register, strip off the first char which should be a $
        string subString = stringToParse.substr(1, string::npos);
        integerValue = atoi(subString.c_str());
    } else if(stringToParse[0] == ':') {
        foundLabel = 1;
    } else {
        try {
            // treat this stringToParse as a number, parse as is
            integerValue = atoi(stringToParse.c_str());
        }
        catch (invalid_argument e) {
            cerr << "Exception! String: " << stringToParse <<
            " was not a valid hex value, register value, or integer value";
            exit(1);
        }
    }

    // if aText doesn't exist then populate a
    if (curInstruction.aText.empty()) {
        if(!foundLabel) {
            curInstruction.a = integerValue;
            curInstruction.aText = stringToParse;
        }
        else {
            curInstruction.aText = stringToParse;
            curInstruction.aLabel = stringToParse;
        }
    }
    else {
        // otherwise, populate b
        if(!foundLabel) {
            curInstruction.b = integerValue;
            curInstruction.bText = stringToParse;
        }
        else {
            curInstruction.bText = stringToParse;
            curInstruction.bLabel = stringToParse;
        }
    }

    return curInstruction;
}

void readFileIntoData(vector<asmData> &programData, string filename) {
    ifstream file;
    file.open(filename);
    if (file.good()) {
        string line;
        while (getline(file, line)) {
            programData.push_back((asmData) {.data = line});
        }
    }
    else {
        throw invalid_argument("Invalid @file argument (doesn't exist): " + filename);
    }

    // it is not necessary to close the file here since ifstream is a proper RAII object
    // but it looks better to me ;)
    file.close();
}

void writeMemFile(string asmFileName, vector<asmData> &programData, vector<asmInstruction> &programInstructions) {
    asmFileName.replace(asmFileName.find(".asm"), 4, ".mem");

    ofstream memFile;

    // open the file, but truncate (clear) the file first
    memFile.open(asmFileName, ofstream::out | ofstream::trunc);

    // When we are extending hex to 4 wide fill with 0's
    memFile << setfill('0') << hex << setw(4) << uppercase;


    int curDataPos = 0;

    memFile << "// data" << endl;
    memFile << "// Begin placeholders for LCD memory" << endl;

    // Leave some place in the memory for the screen glyphs
    /*
    for (int i = 0; i < 1020; i++) {
        memFile << "@" << setw(4) << curDataPos << " 0000_0000_0000_0000" << endl;
        curDataPos++;
    }
     */

    memFile << "// Begin Glyphs" << endl;

    // Then put the character glyphs in the memory
    for (auto &data : programData) {
        memFile << "@" << std::hex << setw(4) << std::uppercase << curDataPos;
        memFile << " " << data.data << endl;

        curDataPos++;
    }

    memFile << "// text" << endl;

    int instructionCount = programInstructions.size();
    int curInstruction = 1;

    // Instructions need to go in the file in reverse order
    std::reverse(programInstructions.begin(), programInstructions.end());
    for (auto &instruction : programInstructions) {

        int instructionLine = 0x3FFF - instructionCount + curInstruction;

        memFile << "@" << std::hex << setw(4) << std::uppercase << instructionLine << " ";

        if(!instruction.aLabel.empty()) {

            // find where a should point to
            // and set a

            int aPos = 0;

            for(auto &tmpInstruction : programInstructions) {
                if(tmpInstruction.lineLabel == instruction.aLabel) {
                    instruction.a = instructionCount - aPos;
                    break;
                }

                aPos++;
            }

        }

        if(!instruction.bLabel.empty()) {

            // find where b should point to
            // and set b

            int bPos = 0;

            for(auto &tmpInstruction : programInstructions) {
                if(tmpInstruction.lineLabel == instruction.aLabel) {
                    instruction.b = instructionCount - bPos;
                    break;
                }

                bPos++;
            }
        }

        // The first instruction code is always present
        memFile << instruction.instruction.code << "_";

        if (instruction.instruction.type == RTYPE) {
            memFile << setw(4) << bitset<4>(instruction.a) << "_";
            memFile << setw(4) << instruction.instruction.extCode << "_";
            memFile << setw(4) << bitset<4>(instruction.b);
        }
        else if (instruction.instruction.type == NOOP) {
            memFile << "0000_0000_0000";
        }
        else if (instruction.instruction.type == ITYPE) {
            memFile << setw(4) << bitset<4>(instruction.a) << "_";
            memFile << setw(4) << bitset<4>(instruction.b >> 4) << "_";
            memFile << setw(4) << bitset<4>(instruction.b & 0xF);
        }
        else if (instruction.instruction.type == JTYPE) {
            memFile << setw(4) << bitset<4>(instruction.a) << "_";
            memFile << "0000_0000";
        }
        else if (instruction.instruction.type == MTYPE) {
            memFile << setw(4) << bitset<4>(instruction.a) << "_";
            memFile << "0000_";
            memFile << setw(4) << bitset<4>(instruction.b);
        }
        else if (instruction.instruction.type == WTYPE) {
            memFile << setw(4) << bitset<4>((instruction.a >> 8) & 0xF) << "_";
            memFile << setw(4) << bitset<4>((instruction.a >> 4) & 0xF) << "_";
            memFile << setw(4) << bitset<4>(instruction.a & 0xF);
        }
        else if (instruction.instruction.type == WLSTYPE) {
            memFile << instruction.instruction.extCode << "_";
            memFile << setw(4) << bitset<4>((instruction.a >> 4) & 0xF) << "_";
            memFile << setw(4) << bitset<4>(instruction.a & 0xF);
        }
        else if (instruction.instruction.type == BTYPE) {
            memFile << setw(4) << bitset<4>(instruction.a >> 8) << "_";
            memFile << setw(4) << bitset<4>((instruction.a >> 4) & 0xF)<< "_";
            memFile << setw(4) << bitset<4>((instruction.a) & 0xF);

        }

        // Add a comment so debugging is easier
        memFile << " // " << instruction.instructionName << " ";

        memFile << instruction.aText << " ";

        memFile << instruction.bText;

        memFile << endl;

        curInstruction++;
    }

    memFile.close();
}

int main(int argc, char *argv[]) {
    map<string, asmType> asmCollection = initAsmCollection();
    vector<asmInstruction> programInstructions;
    vector<asmData> programData;

    ifstream infile(argv[1]);

    if (infile.good()) {

        stringstream iss;
        string section;
        string line;
        string label;
        bool nextInstructionHasLabel = false;

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
                        if (token[0] == '.') {
                            // if token starts with a . then we are changing sections
                            section = token.substr(1);
                        }
                        else if ((token[0] == '/') && (token[1] == '/')) {
                            // if the token is // then we are done with this line, go to the next line
                            // we do this by clearing the stringstream (a.k.a setting it equal to an empty string)
                            iss.str(std::string());
                        }
                        else if (token[0] == ':') {
                            nextInstructionHasLabel = true;
                            label = token;
                        }
                        else {
                            if (section == "data") {
                                if (token == "@file") {
                                    // get the next token since that is the filename
                                    // we want to import into the data vector
                                    getline(iss, token, ' ');
                                    readFileIntoData(programData, token);
                                }
                                else {
                                    // Manual data is not supported right now
                                    /*
                                    int data = parseStringAsInt(token);
                                    asmData curData = (asmData) {
                                            .data = token
                                    };
                                    programData.push_back(curData);
                                     */
                                }
                            }
                            else {
                                if (asmCollection.find(token) != asmCollection.end()) {
                                    string curInstructionName = token;
                                    // get argument A skipping any empty space
                                    getline(iss, token, ' ');
                                    while (token.empty() && getline(iss, token, ' '));

                                    asmInstruction curInstruction;
                                    curInstruction.instruction     = asmCollection[curInstructionName];
                                    curInstruction.instructionName = curInstructionName;

                                    if(nextInstructionHasLabel) {
                                        curInstruction.lineLabel = label;

                                        // reset the label information
                                        nextInstructionHasLabel = false;
                                        label = string();
                                    }

                                    // parse the current token as an instruction and populate the a argument
                                    parseStringAsArgument(curInstruction, token);

                                    if (asmCollection[curInstructionName].arguments == 2) {
                                        // get argument B
                                        getline(iss, token, ' ');
                                        while (token.empty() && getline(iss, token, ' '));

                                        parseStringAsArgument(curInstruction, token);
                                    }

                                    programInstructions.push_back(curInstruction);
                                }
                                else {
                                    throw invalid_argument("Invalid assembly instruction found: " + token);
                                }
                            }
                        }
                    }
                }

                iss.clear();
            }
        }

    } else {
        throw invalid_argument("File does not exist " + string(argv[1]));
    }

    // we are done reading in the asm file
    infile.close();


    // write the file!
    writeMemFile(argv[1], programData, programInstructions);

    return 0;
}

