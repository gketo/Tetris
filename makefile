# ============================
# Basic Makefile (unchanged)
# ============================

# Compiler
CXX = clang++
CXXFLAGS = -fcolor-diagnostics -fansi-escape-codes -std=c++20 -IApp/include -ICore/include

# Source files
APP_SRC = $(wildcard App/*.cpp)
CORE_SRC = $(wildcard Core/*.cpp)
SRC = $(APP_SRC) $(CORE_SRC)

# Target name: use first .cpp in App/ as default
TARGET = $(basename $(notdir $(firstword $(APP_SRC))))

# Default: build the executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Build and run in one command
run: $(TARGET)
	./$(TARGET)

# Clean executable
clean:
	rm -f $(TARGET)

# ============================
# Enhanced section: run-with-log
# ============================

# Named pipe for logs
LOG_PIPE = /tmp/my_log_pipe

run-with-log: $(TARGET)
	# create FIFO if it doesn't exist
	@mkfifo $(LOG_PIPE) || true
	# open a new terminal to read logs
	@osascript -e 'tell application "Terminal" to do script "cat $(LOG_PIPE)"'
	# small delay to ensure terminal is ready
	@sleep 0.5
	# run program with DEBUG_TTY pointing to FIFO
	@export DEBUG_TTY=$(LOG_PIPE); ./$(TARGET)

clean-pipe:
	rm -f /tmp/my_log_pipe