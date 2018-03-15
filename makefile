build:
	g++ *.cpp -O3 -std=c++11
run:
	g++ *.cpp --std=c++11 && (./a.out $(A); rm a.out)
gen:
	cd gentest && cargo +nightly run --release
