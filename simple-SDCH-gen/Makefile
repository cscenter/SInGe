pzip: main.o suffix_automaton.o dictionary.o node.o substring.o 
	g++ main.o suffix_automaton.o dictionary.o node.o substring.o -o pzip

main.o: main.cpp
	g++ -c -O2 -Wall -std=c++11 main.cpp

suffix_automaton.o: suffix_automaton.cpp suffix_automaton.hpp
	g++ -c -O2 -Wall -std=c++11 suffix_automaton.cpp

node.o: node.cpp node.hpp
	g++ -c -O2 -Wall -std=c++11 node.cpp

dictionary.o: dictionary.cpp dictionary.hpp
	g++ -c -O2 -Wall -std=c++11 dictionary.cpp

substring.o: substring.cpp substring.hpp
	g++ -c -O2 -Wall -std=c++11 substring.cpp

