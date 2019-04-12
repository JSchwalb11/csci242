c = gcc
CFLAGS = -Wall
LDFLAGS = -lm
OBJFILES = array_util.o file_util.o
DATAFILES = random_data.txt sorted_data.txt plot_data.txt nlogn_time.txt
TARGET = merge

all: $(TARGET)

$(TARGET): $(OBJFILES)
	    $(c) merge.c -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	    rm -f $(TARGET) $(OBJFILES) $(DATAFILES)
