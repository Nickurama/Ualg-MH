CPPC = g++
CFLAGS = -std=c++20 -O2
# CFLAGS = -std=c++17 -O2 -DNDEBUG
LDFLAGS = -Wall -Wextra -Wpedantic
SRCFILES = $(wildcard src/*.cpp)

build/maxsat: $(SRCFILES)
	$(CPPC) $(CFLAGS) -o build/maxsat $(SRCFILES) $(LDFLAGS) -I include

.PHONY: run clean

run: build/maxsat
	./build/maxsat

clean:
	rm -f build/maxsat
