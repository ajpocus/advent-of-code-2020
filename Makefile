CC        := g++
LD        := g++
CFLAGS += -I$(path)/src

SRC_DIR   = src
BUILD_DIR = build

SRC       = src
OBJ       := $(patsubst src/%.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
    $(CC) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

checkdirs: $(BUILD_DIR)

common:
	g++ -std=c++11 -O3 -Wall -o build/common.o -c src/common.cpp

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

%:
	g++ -std=c++11 -O2 -Wall -Werror src/$@.cpp build/common.o -o bin/$@

