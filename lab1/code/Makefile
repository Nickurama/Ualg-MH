CPPC = g++
CFLAGS = -std=c++20 -O2
# CFLAGS = -std=c++17 -O2 -DNDEBUG
LDFLAGS = -Wall -Wextra -Wpedantic
SRCFILES = $(wildcard src/*.cpp)
INCLUDES = include src
PROJECT = maxsat

FORMATTED_INCLUDES = $(addprefix -I,$(INCLUDES))

build/$(PROJECT): $(SRCFILES)
	$(CPPC) $(CFLAGS) $(FORMATTED_INCLUDES) -o build/$(PROJECT) $(SRCFILES) $(LDFLAGS)

.PHONY: run clean

run: build/$(PROJECT)
	./build/$(PROJECT) $(ARGS)

clean:
	rm -f build/$(PROJECT)
