CC := gcc
BUILD := build
TARGET := main

CPPFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2`
CFLAGS = -Wall -Wextra -lm
LDFLAGS := $(sdl2-config --cflags --libs)
LDLIBS := -lm -lSDL2_image -lSDL2 `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl2` -lpthread

RELEASE := 1
ifneq ($(RELEASE), 0)
	CFLAGS += -Wall -Wextra -w -O3 `pkg-config --cflags --libs sdl`
else
	CFLAGS += -g -O0 -fsanitize=address,undefined
	LDFLAGS += -fsanitize=address,undefined
	CPPFLAGS += -DDEBUG
endif

CFILES := $(shell find . -name "*.c")
OFILES := $(CFILES:%.c=$(BUILD)/%.o)
DFILES := $(OFILES:%.o=%.d)

SRCDIRS := $(shell find . -type d -not -path "*build*")
$(shell mkdir -p $(SRCDIRS:%=$(BUILD)/%))

all: $(TARGET)

$(TARGET): $(OFILES)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)  $(CPPFLAGS)



$(BUILD)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)


clean:
	rm -rf $(BUILD) $(TARGET)
	rm -rf test.txt
	rm -rf ./Solver/test_grid_01.result
	rm -rf ./grid.result
	rm -rf ./grid.txt
	rm -rf *.png
	rm -rf grid.txt
	rm -rf ./cells

.PHONY: all clean

-include $(DFILES)
