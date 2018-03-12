#include "QInt.h"

QInt operator - (const QInt &a) {
        QInt b;
        for (int i = 0; i < N; ++i)
                b.data[i] = ~a.data[i];
        ++b.data[0];
        for (int i = 0; i < N - 1; ++i)
                if (b.data[i] == 0) //overflow
                        ++b.data[i + 1];
        return b;
}
