BUILD_DIR := build
.DEFAULT_GOAL := $(BUILD_DIR)/thread

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/thread: $(BUILD_DIR) src/thread/thread.c
	gcc src/thread/thread.c -o $(BUILD_DIR)/thread

clean::
	rm -rf $(BUILD_DIR)

.PHONY: all
all:: $(BUILD_DIR)/thread
