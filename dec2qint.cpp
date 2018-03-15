#include <stdlib.h>
#include "QInt.h"

static QInt zero() {
    return QInt();
}

static void setbit(QInt &q, int i) {
    q.data[i >> 5] |= 1 << (i & 31);
}

int div2(char *x, int len) {
    char *res = (char *)calloc(len + 1, 1);
    int q     = 0;
    for (int i = 0; i < len; i++) {
        q      = q * 10 + (x[i] - 48);
        res[i] = q / 2 + '0';
        q      = q % 2;
    }

    int start = 0;
    while (start < len && res[start] == '0')
        start++;
    for (int i = start; i <= len; i++)
        res[i - start] = res[i];
    res[len - start] = '\0';
    strcpy(x, res);
    free(res);
    return len - start;
}

QInt Dec2QInt(const char *dec) {
    QInt res = zero();
    int len  = strlen(dec);

    if (len == 0)
        return res;
    int start = dec[0] == '-';
    for (int i = start; i < len; i++) {
        if (dec[i] > '9' || dec[i] < '0')
            return res;
    }

    char *inp = (char *)malloc(len + 1);
    strcpy(inp, dec);
    if (start) {
        memmove(inp, inp + 1, len);
        len -= 1;
    }

    for (int i = 0; i < 127; i++) {
        if (len == 0)
            break;
        if (inp[len - 1] & 1)
            setbit(res, i);
        len = div2(inp, len);
    }

    if (start)
        return -res;
    return res;
}
