include $(DEVKITPPC)/wii_rules

TARGET := ps4-simulator-wii
BUILD := build
SOURCES := source
DATA := data
INCLUDES :=

CFLAGS := -g -O2 -Wall $(MACHDEP) $(INCLUDE)
CXXFLAGS := $(CFLAGS) -std=gnu++17
LDFLAGS := -g $(MACHDEP) -Wl,-Map,$(notdir $@).map

LIBS := -lwiiuse -lbte -logc -lm

# O wii_rules fornece as regras de compilacao e gera o executavel .dol.
include $(DEVKITPPC)/wii_rules
