#include <stdio.h>
#include "QInt.h"

static QInt LogicalShiftLeft(const QInt &q, unsigned int bits) {
    QInt res;
    unsigned int s      = bits >> 5;  // bits / 32
    bits                = bits & 31;
    unsigned int outbit = 32 - bits;

    uint32_t out = 0;

    for (int i = 0; i + s < N; i++) {
        res.data[i + s] = (q.data[i] << bits) | out;
        out             = (outbit >= 32 ? 0 : (q.data[i] >> outbit));
    }

    return res;
}

QInt operator<<(const QInt &q, unsigned int bits) {
    return LogicalShiftLeft(q, bits);
}

static QInt LogicalShiftRight(const QInt &q, unsigned int bits) {
    QInt res;
    unsigned int s      = bits >> 5;  // bits / 32
    bits                = bits & 31;
    uint32_t outmask    = (1u << bits) - 1;
    unsigned int outbit = 32 - bits;

    uint32_t out = 0;

    for (int i = N - 1; i >= (int)s; i--) {
        res.data[i - s] = (q.data[i] >> bits) | out;
        out             = (outbit >= 32 ? 0 : ((q.data[i] & outmask) << outbit));
    }

    return res;
}

QInt operator>>(const QInt &q, unsigned int bits) {
    int sign = q.data[N - 1] >> 31;
    QInt res = LogicalShiftRight(q, bits);

    if (!sign)
        return res;

    int i;
    for (i = N - 1; i >= 0 && res.data[i] == 0; i--)
        res.data[i] = 0xFFFFFFFFu;
    if (i >= 0) {
        for (int j = 31; j >= 0; j--) {
            if ((res.data[i] >> j) & 1)
                break;
            res.data[i] |= 1u << j;
        }
    }

    return res;
}

QInt RotateLeft(const QInt &q, int bits) {
    QInt res;

    unsigned int total_bits = N << 5;

    bits = (bits % total_bits + total_bits) % total_bits;

    unsigned int s       = bits >> 5;  // bits / 32
    bits                 = bits & 31;
    unsigned int outbits = 32 - bits;

    uint32_t out = 0;

    for (int i = 0; i < N; i++) {
        res.data[(i + s) % N] = (q.data[i] << bits) | out;
        out                   = outbits >= 32 ? 0 : (q.data[i] >> outbits);
    }

    res.data[s] |= out;

    return res;
}

QInt RotateRight(const QInt &q, int bits) {
    return RotateLeft(q, -bits);
}
