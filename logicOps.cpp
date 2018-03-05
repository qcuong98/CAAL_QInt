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
