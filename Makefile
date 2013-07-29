CFLAGS=-c -g -Wall

SOURCES=$(shell ls *.cc)
OBJECTS=$(SOURCES:.cc=.o) 
HEADERS=$(SOURCES:.cc=.hh)
MAINO=main.o
EXE=FoldFileGen

$(EXE): $(OBJECTS) $(MAINO) $(HEADERS)
	g++ -g $(OBJECTS) -o $@ -L/user/lipschut/Shell -lNucleus

%.o: %.cc
	g++ $(CFLAGS) $< -o $@

%.hh :
	@

clean:
	rm -f $(OBJECTS) $(MAINO)
	rm -f $(EXE)
