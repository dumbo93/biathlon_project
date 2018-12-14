# cs.bu.edu/teaching/cpp/writing-makefiles/
# the compiler
CC = gcc

# the compiler flag
CFLAGS = -g -Wall

# the linker flag
LDFLAGS = -g -pthread

# the build target executable
TARGET = main

# objectfiles
OBJECTS = main.o save_data.o serial_port_hrm.o serial_port_phy5.o central_state.o

# list of sources
SOURCES = main.c save_data.c serial_port_hrm.c serial_port_phy5.c central_state.c
# *.c **/*.c


# link programs, target: executable
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

# link programs, target: executable
#$(TARGET): $(OBJECTS)
#	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)


# compile programs, target: object files
$(OBJECTS):$(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)


# cleaning
clean:
	rm -f $(TARGET) $(OBJECTS)
