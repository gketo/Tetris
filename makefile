# ============================
# Compiler
# ============================

CXX = clang++

CXXFLAGS = \
	-fcolor-diagnostics \
	-fansi-escape-codes \
	-std=c++20 \
	-I. \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-fsanitize=address,undefined \
	-fno-omit-frame-pointer \
	-g

# ============================
# Source files (recursive, excluding ZExclude)
# ============================

APP_SRC := $(shell find App -name '*.cpp' -not -path '*/ZExclude/*')
CORE_SRC := $(shell find Core -name '*.cpp' -not -path '*/ZExclude/*')

SRC := $(APP_SRC) $(CORE_SRC)

# ============================
# Target
# ============================

TARGET := $(basename $(notdir $(firstword $(APP_SRC))))

# ============================
# Default build
# ============================

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# ============================
# Run
# ============================

run: $(TARGET)
	./$(TARGET)

# ============================
# Logging support
# ============================

LOG_PIPE = /tmp/my_log_pipe

run-log: $(TARGET)
	@mkfifo $(LOG_PIPE) 2>/dev/null || true
	@osascript -e 'tell application "Terminal" to do script "cat $(LOG_PIPE)"'
	@sleep 0.5
	@export DEBUG_TTY=$(LOG_PIPE); ./$(TARGET)

run-log-extra: CXXFLAGS += -DLOG_DEBUG_EXTRA
run-log-extra: $(TARGET)
	@mkfifo $(LOG_PIPE) 2>/dev/null || true
	@osascript -e 'tell application "Terminal" to do script "cat $(LOG_PIPE)"'
	@sleep 0.5
	@export DEBUG_TTY=$(LOG_PIPE); ./$(TARGET)

clean-pipe:
	rm -f $(LOG_PIPE)

# ============================
# Clean
# ============================

clean:
	rm -f $(TARGET)

re: clean all

# ============================
# Debug helpers
# ============================

print-src:
	@echo $(SRC)

print-app:
	@echo $(APP_SRC)

print-core:
	@echo $(CORE_SRC)

# ============================
# Phony targets
# ============================

.PHONY: all run clean re run-log run-log-extra clean-pipe \
	print-src print-app print-core