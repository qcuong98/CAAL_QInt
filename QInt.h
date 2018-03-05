#ifndef _QINT_H_
#define _QINT_H_

#include <cstdint>

struct QInt {
        uint32_t data[4];
        QInt() {
                memset(data, 0, sizeof(data));
        }
};
#endif