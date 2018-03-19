build:
	g++ *.cpp -std=c++11 -O3 -fsanitize=address,undefined -fno-omit-frame-pointer
run:
	@make --no-print-directory
	(./a.out $(A); rm a.out)
gen:
	cd gentest && cargo +nightly run --release
debug:
	g++ *.cpp -std=c++11 -g
