build:
	g++ *.cpp -std=c++11 -O3 #-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined
run:
	@make --no-print-directory
	(./a.out $(A); rm a.out)
gen:
	cd gentest && cargo +nightly run --release
