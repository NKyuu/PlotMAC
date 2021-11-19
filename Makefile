all: libs url_terminal url_png local_terminal local_png

build:
	@ mkdir -p build

libs: build
	@ mkdir -p build/.libs

lib_png: libs
	gcc -c src/libs/plot.c -o build/.libs/libpng.a -Isrc/libs
	echo "Compiling png plot lib\n"

lib_terminal: libs
	gcc -c src/libs/terminal.c -o build/.libs/libterminal.a -Isrc/libs
	echo "Compiling terminal plot lib\n"

lib_url: libs
	gcc -c -fPIC src/libs/dataurl.c -o build/.libs/liburl.so -Isrc/libs
	echo "Compiling url data loading lib\n"

lib_local: libs
	gcc -c -fPIC src/libs/data.c -o build/.libs/liblocal.so -Isrc/libs
	echo "Compiling local file data loading lib\n"

url_terminal: lib_url lib_terminal
	gcc -o build/url_terminal src/main.c -I/build/.libs -L/build/.libs -lurl -lterminal
	echo "Compiling url_terminal\n"

url_png: lib_url lib_png
	gcc -o build/url_png src/main.c -I/build/.libs -L/build/.libs -lurl -lpng
	echo "Compiling url_png\n"

local_terminal: lib_local lib_terminal
	gcc -o build/local_terminal src/main.c -I/build/.libs -L/build/.libs -llocal -lterminal
	echo "Compiling local_terminal\n"

local_png: lib_local lib_png
	gcc -o build/local_png src/main.c -I/build/.libs -L/build/.libs -llocal -lpng
	echo "Compiling local_png\n"
  
clean:
	rm -f build