# Sinh, chạy test

Sinh lại test:
- Cài rust: `curl https://sh.rustup.rs -sSf | sh`
- Cài rust nightly: `rustup install nightly`
- Sinh test: `make gen`

Chạy test:
- Chạy tất cả các test: `python3 test.py`
- Chạy một số test: `python3 test.py tests/01_and tests/04_not`

# Chạy bằng Makefile

```
A=input.txt make run # Không có file output, xuất màn hình
A='input.txt output.txt' make run # Có file output
```

# Định dạng test

```
10 16 123123123 // Chuyển đổi hệ cơ số 10 - 16
10 1231231 - // Tính -x, hệ 10
10 321312313 ~ // Tính ~x
10 1231231 rol 12 // Xoay trái
10 1231231 ror 21 // Xoay phải
.....
```
