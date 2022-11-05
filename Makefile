CC := gcc
BUILD := build
TARGET := main

CPPFLAGS = -MMD `pkg-config --cflags --libs sdl` -lSDL_gfx -lSDL_image 
CFLAGS =
LDFLAGS := $(sdl2-config --cflags --libs) 
LDLIBS := -lm `pkg-config --libs sdl`

RELEASE := 1
ifneq ($(RELEASE), 0)
	CFLAGS += -Wall -Wextra -O3 `pkg-config --cflags --libs sdl`
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
	rm -rf *.bmp

.PHONY: all clean

-include $(DFILES)
