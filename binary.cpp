#include <assert.h>
#include <stdlib.h>
#include "QInt.h"

static void reverse(char *s, int len) {
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char tmp = s[i];
        s[i]     = s[j];
        s[j]     = tmp;
    }
}

char *QInt2Bin(const QInt &input) {
    int len          = 128;
    bool is_negative = input.data[N - 1] >> 31;
    QInt q           = is_negative ? -input : input;
    char *s          = (char *)calloc(len + 2, 1);
    for (int i = 0; i < len; i++) {
        s[i] = ((q.data[i >> 5] >> (i & 31)) & 1) + '0';
    }
    while (len > 1 && s[len - 1] == '0')
        len--;
    if (is_negative) {
        s[len] = '-';
        len++;
    }
    s[len] = '\0';
    reverse(s, len);
    return s;
}

QInt Bin2QInt(const char *s) {
#define IS_VALID_DIGIT(C) \
    ((C) == '0' || (C) == '1')
    const int MAX_LEN = 128;
    QInt q;
    int len = strlen(s);
    if (len == 0)
        return q;
    bool is_negative = s[0] == '-';
    int start        = is_negative ? 1 : 0;
    for (int i = start; i < len; i++) {
        if (!IS_VALID_DIGIT(s[i]))
            return q;
    }
    if (len - start > MAX_LEN)
        return q;
    for (int i = len - 1 - start, p = start; i >= 0; i--, p++) {
        q.data[i >> 5] |= (s[p] - '0') << (i & 31);
    }
    return is_negative? -q : q;
}
