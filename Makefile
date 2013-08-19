CFLAGS=-c -g -Wall

SOURCES=$(shell ls *.cc)
OBJECTS=$(SOURCES:.cc=.o) 
HEADERS=$(shell ls *.hh)
MAINO=main.o
EXE=FoldFileGen

$(EXE): $(OBJECTS) $(MAINO) $(HEADERS)
	@echo "Building" $(EXE)
	@g++ -g $(OBJECTS) -o $@ -L/user/lipschut/Shell -lNucleus
	@echo
	@echo "Build Succeed"

%.o: %.cc
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