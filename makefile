build:
	g++ *.cpp -std=c++11 -O3 #-ggdb -fsanitize=address -fno-omit-frame-pointer
run:
	g++ *.cpp -O3 --std=c++11 && (./a.out $(A); rm a.out)
gen:
	cd gentest && cargo +nightly run --release
