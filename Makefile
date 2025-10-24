# Makefile for Discord Bot
# Compiler and flags
CC = /usr/sbin/gcc
CFLAGS = -fdiagnostics-color=always -std=c17 -pthread -Iinclude -ffunction-sections -fdata-sections -flto
LDFLAGS = -Wl,--gc-sections -flto
LIBS = -ldiscord -lcurl

# Directories
SRC_DIR = src
CMD_DIR = $(SRC_DIR)/commands
HANDLERS_DIR = $(CMD_DIR)/handlers
HELPERS_DIR = $(CMD_DIR)/helpers
UTILITY_DIR = $(CMD_DIR)/utility
PARAM_OPTIONS_DIR = $(SRC_DIR)/poptions

# Output executable
TARGET = myBot.out

# Source files
SOURCES = $(SRC_DIR)/main.c \
          $(HANDLERS_DIR)/slash_commands.c \
		  $(HELPERS_DIR)/message_commands.c \
		  $(HELPERS_DIR)/register_guild_commands.c \
          $(HELPERS_DIR)/purge.c \
          $(UTILITY_DIR)/ping.c \
          $(UTILITY_DIR)/purge.c \
          $(PARAM_OPTIONS_DIR)/options.c \
          $(PARAM_OPTIONS_DIR)/params.c \

# Object files (replace .c with .o)
OBJECTS = $(SOURCES:.c=.o)

# Header dependencies
HEADERS = include/commands.h \
          include/helpers.h \
		  include/handlers.h \
		  include/options.h \
		  include/params.h \

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

clean-artifacts:
	rm -f $(OBJECTS)

# Strip the executable to reduce size
strip: $(TARGET)
	strip $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the bot
run: $(TARGET)
	@./startBot

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Release build with optimizations
release: CFLAGS += -O2 -DNDEBUG
release: $(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all        - Build the bot (default)"
	@echo "  clean      - Remove build artifacts"
	@echo "  clean-artifacts - Remove only object files"
	@echo "  rebuild    - Clean and build"
	@echo "  run        - Build and run the bot"
	@echo "  debug      - Build with debug flags"
	@echo "  release    - Build with optimizations"
	@echo "  strip      - Strip the executable to reduce size"
	@echo "  help       - Show this help message"

# Declare phony targets
.PHONY: all clean clean-artifacts rebuild install-deps run debug release help