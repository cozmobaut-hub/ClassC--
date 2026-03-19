# COMMENTS BEGIN WITH A HASH

# THE NAME OF YOUR PROJECT
PROJECT = L4C
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp
# ALL HEADER FILES THAT ARE PART OF THE PROJECT
H_FILES =
# ANY OTHER RESOURCES FILES THAT ARE PART OF THE PROJECT
REZ_FILES =
# YOUR USERNAME
USERNAME = austin_haas

# NO EDITS BELOW THIS LINE
CXX = g++
CXXFLAGS_DEBUG = -g -O0
CXXFLAGS_WARN = -Wall -Wextra -Wconversion -Wdouble-promotion -Wunreachable-code -Wshadow -Wpedantic
CPPVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ARCHIVE_EXTENSION = zip

ifeq ($(shell echo "Windows"), "Windows")
	TARGET = $(PROJECT).exe
	DEL = del
	ZIPPER = tar -a -c -f
	ZIP_NAME = $(PROJECT)_$(USERNAME).$(ARCHIVE_EXTENSION)
	Q =
	INC_PATH = C:/mingw64/include/
	LIB_PATH = C:/mingw64/lib/
	RPATH =
else
	TARGET = $(PROJECT)
	DEL = rm -f
	ZIPPER = tar -acf
	Q= "
	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
		RPATH =
	endif
	ifeq ($(UNAME_S),Darwin)
		CXXFLAGS += -D OSX
		RPATH = -Wl,-rpath,/Library/Frameworks -Wl,-rpath,$(LIB_PATH)
	endif

	ifeq ($(shell tar --version | grep -o "GNU tar"), GNU tar)
		ARCHIVE_EXTENSION = tar.gz
	endif

	ZIP_NAME = $(PROJECT)_$(USERNAME).$(ARCHIVE_EXTENSION)
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(RPATH) -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CPPVERSION) $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARN) -o $@ -c $< -I$(INC_PATH)

clean:
	$(DEL) $(TARGET) $(OBJECTS)

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) $(CPPVERSION) -MM $(SRC_FILES) >> Makefile

submission:
	@echo "Creating submission file $(ZIP_NAME) ..."
	@echo "...Zipping source files:   $(SRC_FILES) ..."
	@echo "...Zipping header files:   $(H_FILES) ..."
	@echo "...Zipping resource files: $(REZ_FILES)..."
	@echo "...Zipping Makefile..."
	$(ZIPPER) $(ZIP_NAME) $(SRC_FILES) $(H_FILES) $(REZ_FILES) Makefile
	@echo "...$(ZIP_NAME) done!"

.PHONY: all clean depend submission

# DEPENDENCIES
main.o: main.cpp 
