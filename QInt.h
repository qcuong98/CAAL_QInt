#ifndef _QINT_H_
#define _QINT_H_

#include <cstdint>
#include <cstring>

#define N 4

#define BIT (N << 5)

struct QInt {
        uint32_t data[N];
        QInt();
};

QInt operator | (const QInt &, const QInt &);
QInt operator & (const QInt &, const QInt &);
QInt operator ^ (const QInt &, const QInt &);
QInt operator ~ (const QInt &);
QInt operator - (const QInt &a);
QInt operator + (const QInt &a, const QInt &b);
QInt operator - (const QInt &a, const QInt &b);

QInt Dec2QInt(const char *dec);
char *QInt2Dec(const QInt &q);

#endif
