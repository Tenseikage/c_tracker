# Compilation et flags
CC := gcc 
CFLAGS := -Wall -std=c17 
BIN := ./bin
BUILD := ./build
SRC := ./src
INC := ./inc
IPATH := -include 

all: $(BIN)/main

$(BIN)/main: $(BUILD)/memtrack_05.o $(BUILD)/track_04.o
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD)/memtrack_05.o: $(SRC)/memtrack_05.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/track_04.o: $(INC)/memtrack_05.h $(SRC)/track_04.c 
	$(CC) $(CFLAGS) $(IPATH) $^ -c -o $@


clean:
	rm -f $(BUILD)/*.o $(BIN)/main