# Compiler
GPP = g++

# Compilation flags
REQUIRED = -Wall -Wextra -Werror -Wfatal-errors
# You can Modify the Compiler below Compiler 
GPPFlags = $(REQUIRED) -std=c++20
Debug = -g

# source and output names
HWNUM = HW2

# Rename this to the name of your main file
SRC = main.cpp element.cpp
MAIN = main.cpp
HEADER =  element.h
OBJ = element.o

#Update this with your first and last name
TARNAME = rowan_townsend

# Target Name. This will be the name of the executable created by running "Make"
TARGET = calculator
# The DEFAULT_GOAL variable will make it so that running "make" without any arguments will run "make calculator"
.DEFAULT_GOAL := $(Target)

# compile
$(TARGET): $(HWNUM).a
	$(GPP) $(GPPFlags) -o $(TARGET) $(MAIN) $<

%.o: %.cpp $(HEADER)
	$(GPP) $(GPPFlags) -c $< -o $@

$(HWNUM).a: $(OBJ)
	ar -rcs $(HWNUM).a $^

# clean
# Running make clean should clean up any unnecessary components
clean:
	rm -f $(TARGET) *.o *.a
	@echo "Removed all object files."

# Debug option "make debug". This enables the GNU Debugger "gdb"
debug: $(SRC)
	$(GPP) $(GPPFlags) ($SRC) $(Debug) -o $(TARGET)
	@echo "Compiled Debug"

package:
#	tar -c Makefile $(SRC) -f $(HWNUM)_$(TARNAME).tar
# 	Uncomment the Below line when you add headerfiles and comment out the above line
	tar -c Makefile $(SRC) $(HEADER) -f $(HWNUM)_$(TARNAME).tar 
