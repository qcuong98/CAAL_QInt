#include "QInt.h"

QInt operator-(const QInt &a, const QInt &b) {
    return a + (-b);
}
