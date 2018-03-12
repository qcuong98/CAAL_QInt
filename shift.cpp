#include "QInt.h"


QInt operator << (const QInt &q, unsigned int bits) {
	QInt res;
	unsigned int s = bits >> 5; //bits / 32
	bits = bits & 31;
	unsigned int outbits = 32 - bits;
	
	uint32_t out = 0;

	for (int i = 0; i + s < N; i++) {
		res.data[i + s] = (q.data[i] << bits) | out;
		out = q.data[i] >> outbits;
	}

	return res;
}

QInt operator >> (const QInt &q, unsigned int bits) {
	QInt res;
	unsigned int s = bits >> 5; //bits / 32
	bits = bits & 31;
	uint32_t outmask =  (1 << bits) - 1;
	unsigned int outbit = 32 - bits;

	uint32_t out = 0;

	for (int i = N - 1; i >= s; i--) {
		res.data[i - s] = (q.data[i] >> bits) | out;
		out = (q.data[i] & outmask) <<  outbit;
	}

	return res;
}

QInt ShiftRotateLeft(const QInt &q, int bits) {
	QInt res;

	bits = (bits % N + N) % N;

	bits = N  << 5; // N*32
        unsigned int s = bits >> 5; //bits / 32
        bits = bits & 31;
        unsigned int outbits = 32 - bits;

        uint32_t out = 0;

        for (int i = 0; i < N; i++) {
                res.data[(i + s) % N] = (q.data[i] << bits) | out;
                out = q.data[i] >> outbits;
        }

	res.data[s] |= out;

        return res;
}

QInt ShiftRotateRight(const QInt &q, int bits) {
        return ShiftRotateLeft(q, -bits);
}
