TARGET=test.exe
BUILD_DIR=build

IUP=C:/LIBC/iup-3.31_Win64_mingw6_lib
CC=gcc
# CC=C:/mingw64-13.2.0-rev1/bin/gcc
CFLAGS =-Os -Wall -pedantic -I$(IUP)/include -Isrc/include
LDFLAGS=-L$(IUP)
LDLIBS =-liup -liupimglib -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32

ISRC=$(wildcard src/*.c)
OBJ=$(ISRC:src/%.c=$(BUILD_DIR)/%.o)

all: bin/$(TARGET)

$(OBJ): $(BUILD_DIR)/%.o : src/%.c
	@echo Compiling $<
	$(CC) $(CFLAGS) -c -o $@ $<

bin/$(TARGET): $(OBJ)
	@echo Linking
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	@echo Done
	
clean:
	del $(BUILD_DIR)\*.o
	@echo Cleaned

run:bin/$(TARGET)
	bin/$(TARGET)
