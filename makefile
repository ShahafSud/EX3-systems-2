#209374487
CXX = clang++
FLG = -Wall -g

all: Demo.exe

Demo.exe: Demo.o catan.o board.o player.o corner.o
	$(CXX) $(FLG) -o Demo.exe Demo.o catan.o board.o player.o corner.o


Demo.o: Demo.cpp
	$(CXX) $(FLG) -c Demo.cpp -o Demo.o



catan.o: catan.cpp catan.hpp board.hpp player.hpp
	$(CXX) $(FLG) -c catan.cpp -o catan.o

board.o: board.cpp board.hpp corner.hpp
	$(CXX) $(FLG) -c board.cpp -o board.o

player.o: player.cpp player.hpp board.hpp
	$(CXX) $(FLG) -c player.cpp -o player.o

corner.o: corner.cpp corner.hpp
	$(CXX) $(FLG) -c corner.cpp -o corner.o

.PHONY: clean all

clean:
	rm -f *.o Demo.exe