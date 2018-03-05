#include "QInt.h"

QInt negativeQInt(const QInt &a) {
        QInt b;
        for (int i = 0; i < 4; ++i)
                b.data[i] = ~a.data[i];
        ++b.data[0];
        for (int i = 0; i < 3; ++i)
                if (b.data[i] == 0) //overflow
                        ++b.data[i + 1];
        return b;
}