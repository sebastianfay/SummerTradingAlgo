# Makefile

# Compiles the niseko file in c++ 11
all:
	g++ -Wall -Werror -pedantic --std=c++11 niseko.cpp -o niseko


# removes the executable for niseko.cpp and all off the stock information .txts
clean:
	rm -rf *.out niseko
