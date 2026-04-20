# COMMENTS BEGIN WITH A HASH

PROJECT = A5
SRC_FILES = main.cpp coordinate.cpp polygon.cpp triangle.cpp quadrilateral.cpp scalenetriangle.cpp isoscelestriangle.cpp equilateraltriangle.cpp rhombus.cpp
H_FILES = coordinate.hpp polygon.hpp triangle.hpp quadrilateral.hpp scalenetriangle.hpp isoscelestriangle.hpp equilateraltriangle.hpp rhombus.hpp
REZ_FILES = polygons.txt
USERNAME = austin_haas

# NO EDITS BELOW THIS LINE
CXX = g++
CXXFLAGS_DEBUG = -g -O0
CXXFLAGS_WARN  = -Wall -Wextra -Wconversion -Wdouble-promotion -Wunreachable-code -Wshadow -Wpedantic
CPPVERSION     = -std=c++17

# SFML 2.5.1 built into /opt/sfml2
SFML2_INC = -I/opt/sfml2/include
SFML2_LIB = -L/opt/sfml2/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = $(SRC_FILES:.cpp=.o)

ARCHIVE_EXTENSION = zip

ifeq ($(shell echo "Windows"), "Windows")
    TARGET = $(PROJECT).exe
    DEL = del
    ZIPPER = tar -a -c -f
    ZIP_NAME = $(PROJECT)_$(USERNAME).$(ARCHIVE_EXTENSION)
    Q =
else
    TARGET = $(PROJECT)
    DEL = rm -f
    ZIPPER = tar -acf
    Q= "

    ifeq ($(shell tar --version | grep -o "GNU tar"), GNU tar)
        ARCHIVE_EXTENSION = tar.gz
    endif

    ZIP_NAME = $(PROJECT)_$(USERNAME).$(ARCHIVE_EXTENSION)
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(SFML2_LIB) $(SFML_LIBS)

.cpp.o:
	$(CXX) $(CPPVERSION) $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARN) $(SFML2_INC) -o $@ -c $<

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
	@echo "...Zipping Makefile ..."
	$(ZIPPER) $(ZIP_NAME) $(SRC_FILES) $(H_FILES) $(REZ_FILES) Makefile
	@echo "...$(ZIP_NAME) done!"

.PHONY: all clean depend submission

# DEPENDENCIES
main.o: main.cpp coordinate.hpp polygon.hpp triangle.hpp quadrilateral.hpp scalenetriangle.hpp isoscelestriangle.hpp equilateraltriangle.hpp rhombus.hpp
coordinate.o: coordinate.cpp coordinate.hpp
polygon.o: polygon.cpp polygon.hpp coordinate.hpp
triangle.o: triangle.cpp triangle.hpp polygon.hpp coordinate.hpp
quadrilateral.o: quadrilateral.cpp quadrilateral.hpp polygon.hpp coordinate.hpp
scalenetriangle.o: scalenetriangle.cpp scalenetriangle.hpp triangle.hpp polygon.hpp coordinate.hpp
isoscelestriangle.o: isoscelestriangle.cpp isoscelestriangle.hpp triangle.hpp polygon.hpp coordinate.hpp
equilateraltriangle.o: equilateraltriangle.cpp equilateraltriangle.hpp triangle.hpp polygon.hpp coordinate.hpp
rhombus.o: rhombus.cpp rhombus.hpp quadrilateral.hpp polygon.hpp coordinate.hpp
