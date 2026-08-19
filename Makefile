# Makefile - Ejercicios calificables de programacion en C
# Sistemas Embebidos 1
#
# Uso:
#   make            -> compila todos los ejercicios en build/
#   make run        -> compila y ejecuta todos los ejercicios en orden
#   make run-01     -> compila y ejecuta unicamente el ejercicio 01
#   make clean      -> borra los binarios generados
#   make help       -> muestra esta ayuda

CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -pedantic -O2
SRCDIR  := ejercicios-de-programacion
BUILD   := build

SRCS := $(wildcard $(SRCDIR)/ejercicio-*.c)
BINS := $(patsubst $(SRCDIR)/%.c,$(BUILD)/%,$(SRCS))

.PHONY: all run clean help

all: $(BINS)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%: $(SRCDIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

run: all
	@for bin in $(sort $(BINS)); do \
		echo "==============================================="; \
		echo ">> $$bin"; \
		echo "==============================================="; \
		./$$bin; \
		echo ""; \
	done

# Ejecutar un ejercicio puntual: make run-01, make run-07, etc.
run-%: all
	@bin=$$(ls $(BUILD)/ejercicio-$**  2>/dev/null | head -n 1); \
	if [ -z "$$bin" ]; then \
		echo "No existe el ejercicio $*"; exit 1; \
	fi; \
	echo ">> $$bin"; ./$$bin

clean:
	rm -rf $(BUILD)

help:
	@echo "make        - compila todos los ejercicios en build/"
	@echo "make run    - compila y ejecuta todos los ejercicios"
	@echo "make run-NN - compila y ejecuta el ejercicio NN (ej: make run-03)"
	@echo "make clean  - elimina los binarios"
