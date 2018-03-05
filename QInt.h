#ifndef _QINT_H_
#define _QINT_H_

#include <cstdint>
#include <cstring>

struct QInt {
        uint32_t data[4];
        QInt() {
                memset(data, 0, sizeof(data));
        }
};

QInt operator | (const QInt &, const QInt &);
QInt operator & (const QInt &, const QInt &);
QInt operator ^ (const QInt &, const QInt &);
QInt operator ~ (const QInt &);
#endif
