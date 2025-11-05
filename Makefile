CC=gcc
OUT=bin/yafl
SRC=src/main.c

build:
	git clone https://github.com/denalisun/yafl.git
	make -C yafl
	mkdir bin
	cp yafl/yafl.exe bin/yafl.exe
	cp yafl/redirector.dll bin/redirector.dll
	$(CC) -o $(OUT) $(SRC) -std=c99 -Wall -Werror

clean:
	rm -rf bin yafl

install:
	cp -a bin/* /usr/bin
