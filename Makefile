default: build

build:
	gcc -g -o snake source/main.c source/backend.c source/frontend.c -lncurses

run: build
	./snake
