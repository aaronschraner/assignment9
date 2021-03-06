CC=g++
LIM=21
winCC=x86_64-w64-mingw32-g++
winCFLAGS=-static -std=c++11 -DWINDOWS -DWINLIMIT=$(LIM)
CFLAGS= -std=c++11 -DWINLIMIT=$(LIM)
A=9
default:
	$(CC) -o assignment$(A) assignment$(A).cpp $(CFLAGS)
windows:
	$(winCC) -o assignment$(A).exe assignment$(A).cpp $(winCFLAGS)
run:
	$(CC) -o assignment$(A) assignment$(A).cpp $(CFLAGS) && ./assignment$(A)
