c = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = array_util.o file_util.o
TARGET = merge

all: $(TARGET)

$(TARGET): $(OBJFILES)
	    $(c) merge.c -o $(TARGET) $(OBJFILES)

clean:
	    rm -f $(TARGET) $(OBJFILES) random_data.txt sorted_data.txt
