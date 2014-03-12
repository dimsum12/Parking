CCP=g++
CFLAGS=-W -Wall
TARGET_DIR=./bin
EXEC=$(TARGET_DIR)/Parking
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
LIBS=-ltp -lncurses -ltcl
LIBPATH=-L/shares/public/tp/tp-multitache
INCPATH=-I/shares/public/tp/tp-multitache

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CCP) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIBS)

main.o: main.cpp
	$(CCP) -o $@ -c $< $(CFLAGS) $(INCPATH)
	
%.o: %.cpp  %.h
	$(CCP) -o $@ -c $< $(CFLAGS) $(INCPATH)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
