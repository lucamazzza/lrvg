CXX = g++
AR = ar
LD = g++
WINDRES = windres
BUILD_DATE = $(shell date +%Y%m%d)

INC = -I../dependencies/glad/include -I../dependencies/glm/include -I../dependencies/freeimage/include
CFLAGS = -Wall -std=c++20 -fPIC -m64 -fexceptions -DBUILD_DATE=$(BUILD_DATE)
RCFLAGS = 
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = -m64

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g -D_DEBUG
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = ../bin/Debug/libengine.dylib

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS)
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = ../bin/Release/libengine.dylib

SOURCES := $(wildcard *.cpp)

BREW := $(shell brew --prefix 2>/dev/null || echo /usr/local)
PKG_GLFW := $(shell pkg-config --exists glfw3 && echo yes)
PKG_FREEIMAGE := $(shell pkg-config --exists freeimage && echo yes)

# TEMPORARY FIX FOR Installed macOS Libs
ifeq ($(PKG_GLFW),yes)
    PKG_CFLAGS_GLFW := $(shell pkg-config --cflags glfw3)
    PKG_LIBS_GLFW  := $(shell pkg-config --libs glfw3)
else
    ifeq ($(shell uname -s),Darwin)
        PKG_CFLAGS_GLFW :=
        PKG_LIBS_GLFW  := -L$(BREW)/lib -lglfw -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
        INC += -I$(BREW)/include
    else
        PKG_CFLAGS_GLFW :=
        PKG_LIBS_GLFW  := -lglfw -lGL -ldl -lm -lpthread
    endif
endif

ifeq ($(PKG_FREEIMAGE),yes)
    PKG_CFLAGS_FREEIMAGE := $(shell pkg-config --cflags freeimage)
    PKG_LIBS_FREEIMAGE  := $(shell pkg-config --libs freeimage)
else
    ifeq ($(shell uname -s),Darwin)
        PKG_CFLAGS_FREEIMAGE :=
        PKG_LIBS_FREEIMAGE  := -L$(BREW)/lib -lfreeimage
        INC += -I$(BREW)/include
    else
        PKG_CFLAGS_FREEIMAGE :=
        PKG_LIBS_FREEIMAGE  := -lfreeimage
    endif
endif

GLAD_SRC := ../dependencies/glad/src/glad.c

OBJ_DEBUG := $(patsubst %.cpp,$(OBJDIR_DEBUG)/%.o,$(SOURCES))
OBJ_DEBUG += $(OBJDIR_DEBUG)/glad.o

OBJ_RELEASE := $(patsubst %.cpp,$(OBJDIR_RELEASE)/%.o,$(SOURCES))
OBJ_RELEASE += $(OBJDIR_RELEASE)/glad.o

.PHONY: all debug release clean before_debug after_debug before_release after_release

all: debug release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)
	test -d $(OUT_DEBUG) || mkdir -p $(dir $(OUT_DEBUG))

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) -shared $(LIBDIR_DEBUG) $(OBJ_DEBUG) -o $(OUT_DEBUG) $(LDFLAGS_DEBUG) $(LIB_DEBUG) $(PKG_LIBS_GLFW) $(PKG_LIBS_FREEIMAGE)

$(OBJDIR_DEBUG)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) $(PKG_CFLAGS_GLFW) $(PKG_CFLAGS_FREEIMAGE) -c $< -o $@

$(OBJDIR_DEBUG)/glad.o: $(GLAD_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $(GLAD_SRC) -o $@

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
	test -d $(OUT_RELEASE) || mkdir -p $(dir $(OUT_RELEASE))

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) -shared $(LIBDIR_RELEASE) $(OBJ_RELEASE) -o $(OUT_RELEASE) $(LDFLAGS_RELEASE) $(LIB_RELEASE) $(PKG_LIBS_GLFW) $(PKG_LIBS_FREEIMAGE)

$(OBJDIR_RELEASE)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) $(PKG_CFLAGS_GLFW) $(PKG_CFLAGS_FREEIMAGE) -c $< -o $@

$(OBJDIR_RELEASE)/glad.o: $(GLAD_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $(GLAD_SRC) -o $@

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

clean: clean_debug clean_release
