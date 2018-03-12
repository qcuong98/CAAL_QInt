#include "QInt.h"

QInt operator | (const QInt &a, const QInt &b) {
    QInt res;
    for (int i=0; i<N; i++) res.data[i] = a.data[i] | b.data[i];
    return res;
}

QInt operator & (const QInt &a, const QInt &b) {
    QInt res;
    for (int i=0; i<N; i++) res.data[i] = a.data[i] & b.data[i];
    return res;
}

QInt operator ^ (const QInt &a, const QInt &b) {
    QInt res;
    for (int i=0; i<N; i++) res.data[i] = a.data[i] ^ b.data[i];
    return res;
}

QInt operator ~ (const QInt &a) {
    QInt res;
    for (int i=0; i<N; i++) res.data[i] = ~a.data[i];
    return res;
}

QInt operator - (const QInt &a) {
        QInt b = ~a;
        ++b.data[0];
        for (int i = 0; i < N - 1; ++i)
                if (b.data[i] == 0) //overflow
                        ++b.data[i + 1];
		else
			break;
        return b;
}
