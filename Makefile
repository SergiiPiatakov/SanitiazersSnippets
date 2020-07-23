CXX		= clang++

.PHONY all: 001 002

001:
	$(CXX) 001_main.cpp -fsanitize=undefined -O2 -o 001_main

002:
	$(CXX) 002_main.cpp -fsanitize=thread -ggdb -std=c++11 -pthread -o 002_main

.PHONY clean:
	$(RM) 001_main
	$(RM) 002_main
