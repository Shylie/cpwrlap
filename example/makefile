BUILD_MODE       ?= Debug

RAYLIB_PATH      ?= $(LIBS_PATH)/raylib
CHIPMUNK_PATH    ?= $(LIBS_PATH)/Chipmunk2D
CPWRLAP_PATH     ?= ..

HEADER_FILES      = 
SOURCE_FILES      = main.cpp
OBJS              = $(patsubst %.cpp, %.o, $(SOURCE_FILES))

INCLUDE_PATHS     = -I$(RAYLIB_PATH)/src -I$(CHIPMUNK_PATH)/include/chipmunk -I$(CPWRLAP_PATH)/include

LDFLAGS          := -L$(RAYLIB_PATH)/src -L$(CHIPMUNK_PATH)/build/$(BUILD_MODE)/src/ -L$(CPWRLAP_PATH) -lraylib -lcpwrlap -lchipmunk -lwinmm -lgdi32 -static $(LDFLAGS)

ifeq ($(BUILD_MODE),Debug)
	CXXFLAGS := -g3 $(CXXFLAGS)
else ifeq ($(BUILD_MODE),Release)
	CXXFLAGS := -O3 $(CXXFLAGS)
	LDFLAGS  := -mwindows $(LDFLAGS)
endif

build: example.exe

run: build
	./example.exe

clean:
	rm -f $(OBJS)
	rm -f example.exe

example.exe: $(OBJS) $(HEADER_FILES)
	g++ $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o example.exe

%.o: %.cpp
	$(CXX) -c $(INCLUDE_PATHS) $(CXXFLAGS) $^ -o $@
