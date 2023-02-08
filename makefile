all: clean compile test

clean:
	rm -f cmake-build-debug/Project1

compile: main.cpp
	g++ -std=gnu++14 -I . -pthread -o cmake-build-debug/Project1 main.cpp Project1SimpleFileModifier.cpp Util.cpp FileChecker.cpp

test:
	cd cmake-build-debug && ./Project1
