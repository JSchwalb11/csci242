c = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES =
TARGET = merge

all: $(TARGET)

$(TARGET): $(OBJFILES)
	    $(c) merge.c -o $(TARGET) $(OBJFILES)

clean:
	    rm -f $(TARGET) $(OBJFILES) random_data.txt sorted_data.txt
