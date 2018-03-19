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

QInt operator << (const QInt &, unsigned int);
QInt operator >> (const QInt &, unsigned int);
QInt ShiftRotateLeft(const QInt &, int);
QInt ShiftRotateRight(const QInt &, int);

QInt operator - (const QInt &);
QInt operator + (const QInt &, const QInt &);
QInt operator - (const QInt &, const QInt &);
QInt operator * (const QInt &, const QInt &);

QInt Dec2QInt(const char *dec);
char *QInt2Dec(const QInt &q);

QInt Hex2QInt(const char *hex);
char *QInt2Hex(const QInt &q);

#endif
