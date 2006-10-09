GCC = g++
OUTPUT = libframework.a

NAMES = Bitmap.cpp string_cast.cpp
SRC = $(NAMES:%.cpp=./src/%.cpp)
OBJ = $(NAMES:%.cpp=./obj/%.o)

INCLUDE = ./include

all : $(OUTPUT)

$(OUTPUT) : $(OBJ)
	ar rcs $(OUTPUT) $(OBJ)

./obj/%.o : ./src/%.cpp
	$(GCC) -c -I$(INCLUDE) $< -o $@

clean :
	rm -f $(OBJ)
