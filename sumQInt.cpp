#include "QInt.h"

QInt sumQInt(const QInt &a, const QInt &b) {
        QInt c;
        bool tmp = 0;
        for (int i = 0; i < 4; ++i) {
                bool new_tmp = (a.data[i] <= INT32_MAX - b.data[i] - tmp && 
                                b.data[i] != INT32_MAX - tmp);
                c.data[i] = a.data[i] + b.data[i] + tmp;
                tmp = new_tmp;
        }
        return c;
}