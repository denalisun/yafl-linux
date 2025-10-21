CC=gcc
OUT=yafl
SRC=src/main.c

build:
	$(CC) -o $(OUT) $(SRC) -std=c99 -Wall -Werror
