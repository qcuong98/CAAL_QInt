#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "QInt.h"
using namespace std;

struct Input {
    int in_base;
    int out_base;
    char op;
    string lhs, rhs;
    Input(const string &&s) {
        stringstream ss(s);
        string a, b, c, d;
        ss >> a >> b >> c >> d;
        stringstream(a) >> in_base;
        if (d.empty()) {
            if (c == "~" || c == "-") {
                // -a, ~a
                out_base = in_base;
                op       = c[0];
                lhs      = b;
                rhs      = "";
            } else {
                // Convert between bases
                stringstream(b) >> out_base;
                op  = '\0';
                lhs = c;
                rhs = "";
            }
        } else {
            // Two-operand operators
            out_base = in_base;
            op       = c[0];
            lhs      = b;
            rhs      = d;
        }
    }

    string output() {
#define check(EXP)         \
    {                      \
        if (!(EXP))        \
            return "Fuck"; \
    }
#define op2(op) QInt2Dec(Dec2QInt(lhs.data()) op Dec2QInt(rhs.data()))
        check(in_base == 10);
        check(out_base == 10);
        unsigned int u;
        int i;
        switch (op) {
            case '\0':
                return QInt2Dec(Dec2QInt(lhs.data()));
            case '~':
                return QInt2Dec(~Dec2QInt(lhs.data()));
            case '-':
                if (rhs.empty())
                    return QInt2Dec(-Dec2QInt(lhs.data()));
                return op2(+);
            case '+':
                return op2(+);
            case '&':
                return op2(&);
            case '|':
                return op2(|);
            case '^':
                return op2 (^);
            case '<':  // <<
                stringstream(rhs) >> u;
                return QInt2Dec(Dec2QInt(lhs.data()) << u);
            case '>':  // >>
                stringstream(rhs) >> u;
                return QInt2Dec(Dec2QInt(lhs.data()) >> u);
            case 'l':  // Rotate left
                stringstream(rhs) >> i;
                return QInt2Dec(ShiftRotateLeft(Dec2QInt(lhs.data()), i));
            case 'r':  // Rotate right
                stringstream(rhs) >> i;
                return QInt2Dec(ShiftRotateRight(Dec2QInt(lhs.data()), i));
            default:
                check(false);
        }
    }
};

int main(int argc, char **argv) {
    if (argc < 2)
        abort();
    ifstream in(argv[1]);
    string line;
    vector<Input> inputs;
    while (getline(in, line))
        inputs.push_back(Input(move(line)));
    string output;
    for (auto input : inputs)
        output += input.output() + "\n";
    if (argc >= 3) {
        ofstream(argv[3]) << output;
    } else {
        cout << output;
    }
}
