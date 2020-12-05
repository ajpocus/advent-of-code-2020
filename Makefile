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

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)
