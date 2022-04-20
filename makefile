BUILD_MODE       ?= Debug

RAYLIB_PATH      ?= $(LIBS_PATH)/raylib
CHIPMUNK_PATH    ?= $(LIBS_PATH)/Chipmunk2D

HEADER_FILES      = include/space.h include/arbiter.h include/body.h include/shape.h include/circleshape.h include/segmentshape.h include/polygonshape.h include/constraint.h include/pinjoint.h
SOURCE_FILES      = source/space.cpp source/arbiter.cpp source/body.cpp source/shape.cpp source/circleshape.cpp source/segmentshape.cpp source/polygonshape.cpp source/constraint.cpp source/pinjoint.cpp
OBJS              = $(patsubst %.cpp, %.o, $(SOURCE_FILES))

INCLUDE_PATHS     = -Iinclude -I$(RAYLIB_PATH)/src -I$(CHIPMUNK_PATH)/include/chipmunk

ifeq ($(BUILD_MODE),Debug)
	CXXFLAGS := -g3 $(CXXFLAGS)
else ifeq ($(BUILD_MODE),Release)
	CXXFLAGS := -O3 $(CXXFLAGS)
endif

all: libcpwrlap.a

libcpwrlap.a: $(HEADER_FILES) $(OBJS)
	ar rvs libcpwrlap.a $(OBJS)

%.o: %.cpp
	g++ -c $(INCLUDE_PATHS) $(CXXFLAGS) $^ -o $@


clean:
	rm -f $(OBJS)
	rm -f libcpwrlap.a
