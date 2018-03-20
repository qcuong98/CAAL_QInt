#ifndef _QINT_H_
#define _QINT_H_

#include <cstdint>
#include <cstring>

#define N 4

struct QInt {
    uint32_t data[N];
    QInt();
};

// Các thao tác and, or, xor, not
QInt operator|(const QInt &, const QInt &);
QInt operator&(const QInt &, const QInt &);
QInt operator^(const QInt &, const QInt &);
QInt operator~(const QInt &);

QInt operator<<(const QInt &, unsigned int);
QInt operator>>(const QInt &, unsigned int);

// Xoay bit, khi số bit cần xoay âm thì
// xoay trái trở thành xoay phải và ngược lại
QInt RotateLeft(const QInt &, int);
QInt RotateRight(const QInt &, int);

// Phép lấy số đối
QInt operator-(const QInt &);

// Các phép toán cộng trừ nhân chia
QInt operator+(const QInt &, const QInt &);
QInt operator-(const QInt &, const QInt &);
QInt operator*(const QInt &, const QInt &);
QInt operator/(QInt, QInt);

// Chuyển đổi giữa QInt và xâu thập phân
QInt Dec2QInt(const char *dec);
char *QInt2Dec(const QInt &q);

// Chuyển đổi từ xâu thập lục phân sang QInt
QInt Hex2QInt(const char *hex);

// Chuyển đổi từ số QInt sang xâu thập lục phân
//
// Khi số cần chuyển âm thì chuyển số đối của nó
// rồi thêm dấu trừ phía trước xâu
char *QInt2Hex(const QInt &q);

// Chuyển đổi từ xâu nhị phân sang QInt
QInt Bin2QInt(const char *bin);

// Chuyển đổi từ số QInt sang xâu nhị phân
//
// Khi số cần chuyển âm thì chuyển số đối của nó
// rồi thêm dấu trừ phía trước xâu
char *QInt2Bin(const QInt &q);

#endif
