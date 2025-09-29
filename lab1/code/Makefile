PROJECT = maxsat
CPPC = g++
CFLAGS = -std=c++20 -O2
# CFLAGS = -std=c++17 -O2 -DNDEBUG
LDFLAGS = -Wall -Wextra -Wpedantic
# SRCFILES = $(wildcard src/*.cpp) $(wildcard src/*.tpp) $(wildcard src/*.ipp)
# SRCFILES = $(shell find src -name "*.cpp" -o -name "*.tpp" -o -name "*.ipp")
SRCFILES = $(shell find src -name "*.cpp")

INCLUDES = include src
ALL_INCLUDES = $(shell find $(INCLUDES) -type d 2>/dev/null)
FORMATTED_INCLUDES = $(addprefix -I,$(ALL_INCLUDES))

build/$(PROJECT): $(SRCFILES)
	$(CPPC) $(CFLAGS) $(FORMATTED_INCLUDES) -o build/$(PROJECT) $(SRCFILES) $(LDFLAGS)

.PHONY: run clean

run: build/$(PROJECT)
	./build/$(PROJECT) $(ARGS)

clean:
	rm -f build/$(PROJECT)
