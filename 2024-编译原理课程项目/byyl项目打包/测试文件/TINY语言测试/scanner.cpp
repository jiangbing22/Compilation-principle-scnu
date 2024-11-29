#include<iostream>
#include<utility>
#include<fstream>
#include<string>
#include<map>
#include<sstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    if (!infile || !outfile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    map<int, string> endmap;
    endmap[1] = "mod";
    endmap[265] = "ID";
    endmap[2] = "Lparen";
    endmap[260] = "ID";
    endmap[67] = "ID";
    endmap[3] = "Rparen";
    endmap[259] = "ID";
    endmap[4] = "mul";
    endmap[69] = "ID";
    endmap[5] = "add";
    endmap[269] = "ID";
    endmap[70] = "ID";
    endmap[6] = "minus";
    endmap[7] = "div";
    endmap[72] = "ID";
    endmap[8] = "num";
    endmap[19] = "branch";
    endmap[20] = "lt";
    endmap[21] = "eq";
    endmap[22] = "gt";
    endmap[264] = "then";
    endmap[87] = "assign-op";
    endmap[23] = "ID";
    endmap[155] = "ID";
    endmap[27] = "ID";
    endmap[272] = "ID";
    endmap[159] = "ID";
    endmap[31] = "ID";
    endmap[40] = "ID";
    endmap[42] = "ID";
    endmap[43] = "ID";
    endmap[45] = "ID";
    endmap[246] = "comments";
    endmap[54] = "ID";
    endmap[257] = "ID";
    endmap[250] = "ID";
    endmap[58] = "ID";
    endmap[88] = "le";
    endmap[89] = "uneq";
    endmap[154] = "ID";
    endmap[90] = "ge";
    endmap[156] = "if";
    endmap[157] = "ID";
    endmap[158] = "ID";
    endmap[160] = "ID";
    endmap[161] = "ID";
    endmap[162] = "ID";
    endmap[164] = "ID";
    endmap[165] = "ID";
    endmap[166] = "ID";
    endmap[167] = "ID";
    endmap[247] = "ID";
    endmap[263] = "ID";
    endmap[248] = "end";
    endmap[249] = "ID";
    endmap[251] = "ID";
    endmap[252] = "ID";
    endmap[253] = "ID";
    endmap[261] = "else";
    endmap[254] = "ID";
    endmap[256] = "ID";
    endmap[258] = "ID";
    endmap[262] = "read";
    endmap[266] = "ID";
    endmap[271] = "ID";
    endmap[273] = "ID";
    endmap[274] = "until";
    endmap[275] = "write";
    endmap[276] = "ID";
    endmap[279] = "repeat";

    string input;
    ostringstream oss;
    string line;
    while (getline(infile, line)) {
        oss << line << '\n';
    }
    input = oss.str();
    int idx = 0;
    string tokenstring;
    while (idx < input.size()) {
        while (idx < input.size() && isspace(input[idx])) {
            idx++;
        }
        if(idx == input.size()){
        break;
        }
        int laststate = -1;
        int state = 0;
        tokenstring = "";

        while (state >= 0 && idx < input.size()) {
            switch (state) {
                    case 0:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '*':
                                state = 4;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '(':
                                state = 2;
                                tokenstring += input[idx];
                                break;
                            case '-':
                                state = 6;
                                tokenstring += input[idx];
                                break;
                            case '%':
                                state = 1;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 54;
                                tokenstring += input[idx];
                                break;
                            case ')':
                                state = 3;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 58;
                                tokenstring += input[idx];
                                break;
                            case '+':
                                state = 5;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '/':
                                state = 7;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case ':':
                                state = 18;
                                tokenstring += input[idx];
                                break;
                            case ';':
                                state = 19;
                                tokenstring += input[idx];
                                break;
                            case '<':
                                state = 20;
                                tokenstring += input[idx];
                                break;
                            case '=':
                                state = 21;
                                tokenstring += input[idx];
                                break;
                            case '>':
                                state = 22;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 27;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 31;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 40;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 42;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 43;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 45;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 67;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 69;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 70;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 72;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '{':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 1:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 2:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 3:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 4:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 5:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 6:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 7:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 8:
                        switch (input[idx]) {
                            case '0':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 8;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 9:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 10:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 11:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 12:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 13:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 14:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 15:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 16:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 17:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 18:
                        switch (input[idx]) {
                            case '=':
                                state = 87;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 19:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 20:
                        switch (input[idx]) {
                            case '=':
                                state = 88;
                                tokenstring += input[idx];
                                break;
                            case '>':
                                state = 89;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 21:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 22:
                        switch (input[idx]) {
                            case '=':
                                state = 90;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 23:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 24:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 25:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 26:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 27:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 154;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 155;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 28:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 29:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 30:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 31:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 156;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 32:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 33:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 34:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 35:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 36:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 37:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 38:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 39:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 40:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 157;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 41:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 42:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 158;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 43:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 159;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 44:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 45:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 160;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 46:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 47:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 48:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 49:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 50:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 51:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 52:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 53:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 54:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 161;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 162;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 55:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 56:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 57:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 58:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 156;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 59:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 60:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 61:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 62:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 63:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 64:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 65:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 66:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 67:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 164;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 68:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 69:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 165;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 70:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 166;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 71:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 72:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 167;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 73:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 74:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 75:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 76:
                        switch (input[idx]) {
                            case 'J':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '\n': 
                                state = 76;
                                break;
                            case 'j':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '*':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case ' ':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '(':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '-':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '%':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case ')':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '+':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '/':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case ':':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case ';':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '<':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '=':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '>':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '^':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 76;
                                tokenstring += input[idx];
                                break;
                            case '}':
                                state = 246;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 77:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 78:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 79:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 80:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 81:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 82:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 83:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 84:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 85:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 86:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 87:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 88:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 89:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 90:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 91:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 92:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 93:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 94:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 95:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 96:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 97:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 98:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 99:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 100:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 101:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 102:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 103:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 104:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 105:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 106:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 107:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 108:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 109:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 110:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 111:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 112:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 113:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 114:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 115:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 116:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 117:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 118:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 119:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 120:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 121:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 122:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 123:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 124:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 125:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 126:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 127:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 128:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 129:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 130:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 131:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 132:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 133:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 134:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 135:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 136:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 137:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 138:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 139:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 140:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 141:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 142:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 143:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 144:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 145:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 146:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 147:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 148:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 149:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 150:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 151:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 152:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 153:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 154:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 247;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 155:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 248;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 156:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 157:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 249;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 250;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 158:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 251;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 159:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 252;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 160:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 253;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 161:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 254;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 162:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 248;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 163:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 164:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 256;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 257;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 165:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 258;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 166:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 259;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 167:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 260;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 168:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 169:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 170:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 171:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 172:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 173:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 174:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 175:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 176:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 177:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 178:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 179:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 180:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 181:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 182:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 183:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 184:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 185:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 186:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 187:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 188:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 189:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 190:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 191:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 192:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 193:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 194:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 195:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 196:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 197:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 198:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 199:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 200:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 201:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 202:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 203:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 204:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 205:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 206:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 207:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 208:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 209:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 210:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 211:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 212:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 213:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 214:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 215:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 216:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 217:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 218:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 219:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 220:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 221:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 222:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 223:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 224:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 225:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 226:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 227:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 228:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 229:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 230:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 231:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 232:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 233:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 234:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 235:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 236:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 237:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 238:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 239:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 240:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 241:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 242:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 243:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 244:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 245:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 246:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 247:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 261;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 248:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 249:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 262;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 250:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 263;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 251:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 264;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 252:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 265;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 253:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 266;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 254:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 261;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 255:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 256:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 262;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 257:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 269;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 258:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 264;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 259:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 271;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 260:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 272;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 261:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 262:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 263:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 273;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 264:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 265:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 274;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 266:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 275;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 267:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 268:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 269:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 276;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 270:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 271:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 274;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 272:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 275;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 273:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 279;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 274:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 275:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 276:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 279;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 277:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 278:
                        switch (input[idx]) {
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    case 279:
                        switch (input[idx]) {
                            case 'J':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'j':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'h':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'e':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'i':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'k':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '0':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '1':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '2':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '3':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '4':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '5':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '6':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '7':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '8':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '9':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'A':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'B':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'C':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'D':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'E':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'F':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'G':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'H':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'I':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'K':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'L':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'M':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'N':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'O':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'P':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'R':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'S':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'T':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'U':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'V':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'W':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'X':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'Z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case '_':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'a':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'b':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'c':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'd':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'f':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'g':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'l':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'm':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'n':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'o':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'p':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'q':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'r':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 's':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 't':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'u':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'v':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'w':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'x':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'y':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            case 'z':
                                state = 23;
                                tokenstring += input[idx];
                                break;
                            default:
                                laststate = state;
                                state = -1;
                                break;
                        }
                        break;
                    default:
                        laststate = state;
                        state = -1;
                        break;
                }
                idx++;
            }

            if (state == -1) {
                if (laststate == 1 || laststate == 2 || laststate == 3 || laststate == 4 || laststate == 5 || laststate == 6 || laststate == 7 || laststate == 8 || laststate == 19 || laststate == 20 || laststate == 21 || laststate == 22 || laststate == 23 || laststate == 27 || laststate == 31 || laststate == 40 || laststate == 42 || laststate == 43 || laststate == 45 || laststate == 54 || laststate == 58 || laststate == 67 || laststate == 69 || laststate == 70 || laststate == 72 || laststate == 87 || laststate == 88 || laststate == 89 || laststate == 90 || laststate == 154 || laststate == 155 || laststate == 156 || laststate == 157 || laststate == 158 || laststate == 159 || laststate == 160 || laststate == 161 || laststate == 162 || laststate == 164 || laststate == 165 || laststate == 166 || laststate == 167 || laststate == 246 || laststate == 247 || laststate == 248 || laststate == 249 || laststate == 250 || laststate == 251 || laststate == 252 || laststate == 253 || laststate == 254 || laststate == 256 || laststate == 257 || laststate == 258 || laststate == 259 || laststate == 260 || laststate == 261 || laststate == 262 || laststate == 263 || laststate == 264 || laststate == 265 || laststate == 266 || laststate == 269 || laststate == 271 || laststate == 272 || laststate == 273 || laststate == 274 || laststate == 275 || laststate == 276 || laststate == 279) {
                    outfile <<""<< endmap[laststate] << " -> " << tokenstring  << endl;
                    idx--;
                } else {
                    outfile << "Invalid token: " << tokenstring << endl;
                }
            } else {
                if (state == 1 || state == 2 || state == 3 || state == 4 || state == 5 || state == 6 || state == 7 || state == 8 || state == 19 || state == 20 || state == 21 || state == 22 || state == 23 || state == 27 || state == 31 || state == 40 || state == 42 || state == 43 || state == 45 || state == 54 || state == 58 || state == 67 || state == 69 || state == 70 || state == 72 || state == 87 || state == 88 || state == 89 || state == 90 || state == 154 || state == 155 || state == 156 || state == 157 || state == 158 || state == 159 || state == 160 || state == 161 || state == 162 || state == 164 || state == 165 || state == 166 || state == 167 || state == 246 || state == 247 || state == 248 || state == 249 || state == 250 || state == 251 || state == 252 || state == 253 || state == 254 || state == 256 || state == 257 || state == 258 || state == 259 || state == 260 || state == 261 || state == 262 || state == 263 || state == 264 || state == 265 || state == 266 || state == 269 || state == 271 || state == 272 || state == 273 || state == 274 || state == 275 || state == 276 || state == 279) {
                    outfile <<""<< endmap[state] << " -> " << tokenstring  << endl;
                } else {
                    outfile << "Invalid token: " << tokenstring << endl;
                }
            }
        }

    infile.close();
    outfile.close();
    return 0;
}
