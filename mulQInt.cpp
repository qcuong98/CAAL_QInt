#include "QInt.h"

QInt operator*(const QInt &a, const QInt &b) {
    QInt res;

    for (int s = N - 1; s >= 0; s--)
        for (int i = 31; i >= 0; i--) {
            res = res << 1;
            if ((b.data[s] >> i) & 1)
                res = res + a;
        }
    return res;
}
