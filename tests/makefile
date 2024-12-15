SRC := ./src
BIN := ./bin
TRACKPATH := ./usr/
LFLAGS := -Wl,-rpath,$(TRACKPATH)lib -L$(TRACKPATH)lib -ltrack
OBJS := $(BIN)/test1.o $(BIN)/test2.o $(BIN)/test3.o $(BIN)/test4.o
TESTS := test1 test2 test3 test4

# Test du traceur
.PHONY: all $(TESTS)

all: $(TESTS)

$(TESTS): % : $(BIN)/%.o
	$(CC) $< $(CFLAGS) $(LFLAGS) -o $@

$(BIN)/%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN)/*.o $(TESTS)