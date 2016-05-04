# minimalist makefile
.SUFFIXES:
#
.SUFFIXES: .cpp .o .c .h
ifeq ($(DEBUG),1)
CXXFLAGS = -fPIC  -std=c++11 -ggdb -march=native -Wall -Wextra -Wshadow -fsanitize=undefined  -fno-omit-frame-pointer -fsanitize=address
else
CXXFLAGS = -fPIC -std=c++11 -O3  -march=native -Wall -Wextra -Wshadow
endif # debug
all: unit  
HEADERS=./include/concise.h ./include/conciseutil.h

unit: ./tests/unit.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o unit ./tests/unit.cpp  -Iinclude
clean:
	rm -f  *.o unit
