#include <iostream>
#include <fstream>
#include <sstream>
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
} data_element;

typedef struct {
    asmType instruction;
    int a;
    int b;
    int immediate;
} text_element;

int main(int argc, char *argv[]) {

    map<string, asmType> asmCollection = initAsmCollection();

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
                            cout << " SECTION: " << section << " TYPE: ";

                            string::size_type size;

                            if (asmCollection.find(token) != asmCollection.end()) {
                                // cout << " " << asmCollection[token].code;
                                cout <<  "instruction";
                            } else if (token.find("0x") != string::npos) {
                                // this token is in hex, strip off the first 2 chars which should be 0x
                                cout << "hex VALUE: " << stoi(&token[2], nullptr, 16);
                            } else if (token.find("$") != string::npos) {
                                // this token is a register, strip off the first char which should be a $
                                cout << "reg VALUE: " << stoi(&token[1], &size);
                            } else {
                                try {
                                    // treat this token as a number, parse as is
                                    cout << "int VALUE: " << stoi(token, &size);
                                }
                                catch(invalid_argument e) {
                                    cout << endl << endl << "Exception! Token: " << token << " was not a valid instruction, hex value, register value, or integer value";
                                    exit(1);
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
