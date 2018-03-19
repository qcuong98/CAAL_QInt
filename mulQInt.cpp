#include "QInt.h"


QInt operator *(const QInt &a, const QInt &b) {
	QInt res;

	for (int s = N - 1; s >= 0; s--) 
		for (int i = 31; i >= 0; i--) {
			if ((b.data[s] >> i) & 1)
				res = res + b;
			res = res << 1;
		}
	return res;

}
