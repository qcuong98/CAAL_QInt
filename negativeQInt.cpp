#include "QInt.h"

QInt operator - (const QInt &a) {
        QInt b = ~a;
        ++b.data[0];
        for (int i = 0; i < N - 1; ++i)
                if (b.data[i] == 0) //overflow
                        ++b.data[i + 1];
        return b;
}
