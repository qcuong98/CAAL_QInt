#include "QInt.h"

int Sign(const QInt &a) {
	if (a.data[N-1] >> 31)
		return -1;

	int i = N - 1;
	while (i >= 0 && a.data[i] == 0) i--;

	return i >= 0;
}

bool operator < (const QInt &a, const QInt &b) {
	int sign = (int)(a.data[N-1] >> 31) - (b.data[N-1] >> 31);
	if (sign != 0) return sign < 0;

	int i = N - 1;
	while (i >= 0 && a.data[i] == b.data[i]) i--;
	return (i >= 0) && (a.data[i] < b.data[i]);
}

int BitCount(const QInt &a) {
	int i = N - 1;

	while (i >= 0 && a.data[i] == 0)

	if (i < 0) return 0;

	int s = 31;
	while (!(a.data[i] >> s)) s--;

	return (i << 5) + s + 1;
}

QInt operator / (QInt a, QInt b) {
	QInt res;
	
	int sign1 = Sign(a);
	int sign2 = Sign(b);

	if (sign2 == 0)
		return res; //NaN div by zero

	if (sign1) a = -a;
	if (sign2) b = -b;
	if (a < b) return res;

	int s = sign1 * sign2;

	int bit = BitCount(a) - BitCount(b);
	b = b << bit;

	while (bit >= 0) {
		bit--;
		res = res << 1;
		if (a < b) continue;

		a = a - b;
		res.data[0] |= 1; //turn to 1
	}
	if (s > 0)
		return res;
	else
		return -res;
}
