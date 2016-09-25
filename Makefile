CC = g++
CFLAGS = -Wall -std=c++11

parser: parser.tab.o lex.yy.o class.o
	$(CC) $(CFLAGS) -o $@ $^
	
parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
	
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
	
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) -std=c++11 -c -o $@ $<
	
lex.yy.c: leks.l
	flex $<

class.o: class.cpp class.hpp
	$(CC) -c $(CFLAGS) $< -o $@
	
.PHONY: clean

clean:
	rm -rf *~ *tab* lex.yy.* *.o parser *.output 