#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>
#include "QInt.h"
using namespace std;

static string to_str(const QInt &q, int base) {
    char *s = NULL;
    if (base == 10)
        s = QInt2Dec(q);
    if (base == 16)
        s = QInt2Hex(q);
    if (base == 2)
        s = QInt2Bin(q);
    if (s == NULL) abort();
    string res(s);
    free(s);
    return res;
}

static QInt from_str(const string &s, int base) {
    if (s.empty())
        return QInt();
    if (base == 10)
        return Dec2QInt(s.data());
    if (base == 16)
        return Hex2QInt(s.data());
    if (base == 2)
        return Bin2QInt(s.data());
    abort();
}

struct Input {
    int in_base;
    int out_base;
    string op;
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
                op       = c;
                lhs      = b;
                rhs      = "";
            } else {
                // Convert between bases
                stringstream(b) >> out_base;
                op  = "conv";
                lhs = c;
                rhs = "";
            }
        } else {
            // Two-operand operators
            out_base = in_base;
            op       = c;
            lhs      = b;
            rhs      = d;
        }
    }

    string output() const {
#define RETURN(EXP) \
    { return to_str(EXP, out_base); }
#define CHECK(EXP)                  \
    {                               \
        if (!(EXP))                 \
            return "Invalid input"; \
    }
#define CASE(x) if (op == x)

        CHECK(in_base == 10 || in_base == 16 || in_base == 2);
        CHECK(out_base == 10 || out_base == 16 || out_base == 2);

        QInt L = from_str(lhs, in_base);

        CASE("conv") RETURN(L);
        CASE("~") RETURN(~L);

        unsigned int u;
        int i;
        CASE("<<") {
            stringstream(rhs) >> u;
            RETURN(L << u);
        }
        CASE(">>") {
            stringstream(rhs) >> u;
            RETURN(L >> u);
        }
        CASE("rol") {
            stringstream(rhs) >> i;
            RETURN(ShiftRotateLeft(L, i));
        }
        CASE("ror") {
            stringstream(rhs) >> i;
            RETURN(ShiftRotateRight(L, i));
        }

        QInt R = from_str(rhs, in_base);
        CASE("-") {
            if (rhs.empty())
                RETURN(-L);
            RETURN(L - R);
        }
        CASE("+") RETURN(L + R);
        CASE("&") RETURN(L & R);
        CASE("|") RETURN(L | R);
        CASE("^") RETURN(L ^ R);
	CASE("*") RETURN(L * R);
	CASE("/") RETURN(L / R);

        CHECK(false);
#undef RETURN
#undef CHECK
#undef CASE
    }
};

int main(int argc, char **argv) {
    if (argc < 2)
        abort();

    ifstream in(argv[1]);
    vector<Input> inputs;
    for (string line; getline(in, line);)
        inputs.push_back(Input(move(line)));

    stringstream output;
    for (auto &input : inputs)
        output << input.output() << endl;

    if (argc >= 3) {
        ofstream(argv[3]) << output.str();
    } else {
        cout << output.str();
    }
}
