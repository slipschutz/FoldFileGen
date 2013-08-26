CFLAGS=-c -g -Wall $(shell root-config --cflags) -I./src -I ./include -std=c++11 
LDLIBS=$(shell root-config --glibs)
LDFLAGS=$(shell root-config --ldflags)



SOURCES=$(shell ls *.cc)
OBJECTS=$(SOURCES:.cc=.o) 
HEADERS=$(shell ls *.hh)
MAINO=main.o
EXE=FoldFileGen

$(EXE): $(OBJECTS) $(MAINO) $(HEADERS)
	@echo "Building" $(EXE)
	g++ -g $(OBJECTS) $(MAINO) $(LDLIBS) -o $@ -L/user/lipschut/Shell -lNucleus
	@echo
	@echo "Build Succeed"

%.o: %.cc %.hh
	@echo "Compiling" $<"..."
	@g++ $(CFLAGS) $< -o $@

%.o: %.C
	@echo "Compiling" $<"..."
	@g++ $(CFLAGS) $< -o $@


clean:
	rm -f $(OBJECTS) $(MAINO)
	rm -f $(EXE)

test:
	@echo $(HEADERS)