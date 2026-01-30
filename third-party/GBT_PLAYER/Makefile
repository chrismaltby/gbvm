GBDK = ../../../gbdk
GBDKLIB = $(GBDK)/lib/small/asxxxx
CC = $(GBDK)/bin/lcc
SDAR = $(GBDK)/bin/sdar

BUILD_DIR = ./build
OBJ_DIR = ./obj

TARGET = $(BUILD_DIR)/gbt_player.lib
OBJS = $(OBJ_DIR)/gbt_player.o

all: directories $(TARGET)

directories: $(BUILD_DIR) $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR)/%.o:	%.s
	$(CC) -c -o $@ $<

$(TARGET): $(OBJS)
	$(SDAR) -ru $@ $^

clean:
	@echo "CLEANUP..."
	rm -rf $(OBJ_DIR)
	rm -rf $(BUILD_DIR)
