# Makefile for q2
# Usage:
#   make              # Compile with q2p1.h (default)
#   make PART=p1      # Compile with q2p1.h
#   make PART=p2      # Compile with q2p2.h
#   make OUTPUT=DEBUG # Any value for OUTPUT enables debug output (default is NOOUTPUT)

OPT := -O2
OUTPUT ?= NOOUTPUT
CXX = g++
CXXFLAGS = -std=c++11 -Wall "${OPT}" -D"${OUTPUT}" 

# Default to part 1
PART ?= p1

IMPL_HEADER = q2$(PART).h

CXXFLAGS += -DUSE_HEADER=\"$(IMPL_HEADER)\"

TARGET = q2
SRC = q2.cc
FLAGS_FILE = .make_flags

# Track flags to detect changes
CURRENT_FLAGS = $(OUTPUT):$(PART)

all: $(TARGET)

# Force rebuild if flags changed
$(FLAGS_FILE): FORCE
	@echo "$(CURRENT_FLAGS)" | cmp -s - $@ || echo "$(CURRENT_FLAGS)" > $@

$(TARGET): $(SRC) $(IMPL_HEADER) ipow.h $(FLAGS_FILE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) $(FLAGS_FILE)

.PHONY: all clean FORCE
