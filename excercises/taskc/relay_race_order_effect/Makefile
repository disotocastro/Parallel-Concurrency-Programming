# Makefile para compilar y ejecutar relay_race_order_effect.c

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c17
LDFLAGS = -pthread
SRC = src/relay_race_order_effect.c
OBJ = build/relay_race_order_effect.o
BIN = bin/relay_race_order_effect
REVERSE_BIN = bin/relay_race_order_effect_reverse

# Objetivo por defecto
all: $(BIN) $(REVERSE_BIN)

# Compilación normal
$(BIN): $(OBJ)
	mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

# Compilación con REVERSE_ORDER
$(REVERSE_BIN): $(OBJ)
	mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(OBJ) -DREVERSE_ORDER -o $@

# Compilar el archivo objeto
$(OBJ): $(SRC)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -rf build bin

# Ejecutar la versión normal
run: $(BIN)
	./$(BIN) 5 100 200

# Ejecutar la versión con REVERSE_ORDER
run-reverse: $(REVERSE_BIN)
	./$(REVERSE_BIN) 5 100 200

.PHONY: all clean run run-reverse
