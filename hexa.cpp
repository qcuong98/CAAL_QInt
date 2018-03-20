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

char *QInt2Hex(const QInt &input) {
    const char *D    = "0123456789ABCDEF";
    int len          = 32;
    bool is_negative = input.data[N - 1] >> 31;
    QInt q           = is_negative ? -input : input;
    char *s          = (char *)calloc(len + 2, 1);
    for (int i = 0; i < len; i++) {
        s[i] = D[(q.data[i >> 3] >> ((i & 7) << 2)) & 15];
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

// Chuyển kí tự c sang giá trị trong hệ hexa
static int digit_to_val(char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    if ('A' <= c && c <= 'F')
        return 10 + c - 'A';
    if ('a' <= c && c <= 'f')
        return 10 + c - 'a';
    throw 0;
}

QInt Hex2QInt(const char *s) {
#define IS_VALID_DIGIT(C) \
    (('0' <= (C) && (C) <= '9') || ('A' <= (C) && (C) <= 'F') || ('a' <= (C) && (C) <= 'f'))
    const int MAX_LEN = 32;
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
        q.data[i >> 3] |= digit_to_val(s[p]) << ((i & 7) << 2);
    }
    return is_negative ? -q : q;
}
