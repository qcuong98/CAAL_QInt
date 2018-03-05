#include "negativeQInt.cpp"
#include "sumQInt.cpp"

QInt SubQInt(const QInt &a, const QInt &b) {
        return sumQInt(a, negativeQInt(b));
}