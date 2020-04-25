
.PHONY: clean help clean-all clean-obj all
# $@ is the recipe name
# $< is the first dependence
# $^ are all the dependencies

# Directories:
INC_DIR     = include
SRC_DIR     = src
BUILD_DIR   = build
OBJ_DIR     = $(BUILD_DIR)/obj
LIB_DIR     = lib

# Excecutables
CPP         = aarch64-linux-gnu-g++
C           = aarch64-linux-gnu-gcc
# CPP         = g++
# C           = gcc
RM          = rm -f

# Flags
CPP_FLAGS   = -I$(INC_DIR) -O3 -std=c++17 -Wall
C_FLAGS     = -I$(INC_DIR) -O3 -std=c17 -Wall
ASM_FLAGS   = -I$(INC_DIR)
LIBS        =
L_FLAGS     = $(LIBS)

# CPP_FLAGS += -DDEBUG

# Souce files
SRCS_C      = $(wildcard $(SRC_DIR)/*.c)
SRCS_CPP    = $(wildcard $(SRC_DIR)/*.cpp)
SRCS_ASM    = $(wildcard $(SRC_DIR)/*.asm)
MAINS       = $(wildcard *.c) \
				$(wildcard *.cpp) \
				$(wildcard *.asm)

# Objects
MAIN_OBJS   = \
	$(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(MAINS))) \
	$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(MAINS))) \
	$(patsubst %.asm,$(OBJ_DIR)/%.o,$(MAINS))

OBJS        = \
	$(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS_C))) \
	$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRCS_CPP))) \
	$(patsubst %.asm,$(OBJ_DIR)/%.o,$(notdir $(SRCS_ASM)))

# OBJS       += $(MAIN_OBJS)

# TARGETS     = \
# 	$(patsubst %.cpp,%,$(notdir $(MAINS))) \
# 	$(patsubst %.c,%,$(notdir $(MAINS)))

# Attempt to create the output directories
ifneq ($(BUILD_DIR),)
$(shell [ -d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR))
$(shell [ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR))
endif


### Rules

# main rule
main: $(OBJS) $(OBJ_DIR)/RGB-ify.o
	$(CPP) -o $(BUILD_DIR)/RGB-ify $^ $(CPP_FLAGS) $(L_FLAGS)

# Mains rules
$(OBJ_DIR)/%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPP_FLAGS)

$(OBJ_DIR)/%.o: %.c
	$(C) -c -o $@ $< $(C_FLAGS)

$(OBJ_DIR)/%.o: %.asm
	$(C) -c -o $@ $< $(ASM_FLAGS)

# Obj rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) -c -o $@ $< $(CPP_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(C) -c -o $@ $< $(C_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	$(C) -c -o $@ $< $(ASM_FLAGS)


clean-obj:
	$(RM) $(OBJ_DIR)/*.o

clean-all:
	$(RM) -r $(BUILD_DIR)

debug:
	@echo $(OBJS)
