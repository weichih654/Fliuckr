CONFPATH     = ../
include $(CONFPATH)/config.mk

NAME        := image_controll
MAJOR       := 0
MINOR       := 1
VERSION     := $(MAJOR).$(MINOR).1

CXXFLAGS    += 
CPPFLAGS    += -I$(THIRD_PARTY_PREFIX)/include/GraphicsMagick -I$(THIRD_PARTY_PREFIX)/include/ -I$(PREFIX)/include/GraphicsMagick -I$(PREFIX)/include/
ifeq ($(PLATFORM), Darwin)
    LDFLAGS     += -fPIC -dynamiclib -undefined suppress -flat_namespace
endif
ifeq ($(PLATFORM), LINUX)
    LDFLAGS     += -fPIC -shared -Wl,-soname,lib$(NAME).so.$(MAJOR)
endif
ifeq ($(PLATFORM), WIN32)
    LDFLAGS     += -fPIC -shared 
endif

LDFLAGS += -L./ -L$(THIRD_PARTY_PREFIX)/lib -L$(PREFIX)/lib -L/opt/lib -L/opt/lib/ -L/usr/X11/lib -L/opt/X11/lib

ifeq ($(PLATFORM), WIN32)
	LIBS        = -limage_core
else
	LIBS        = -limage_core
endif
OBJS        = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

TARGET      = lib$(NAME).so

ifeq ($(PLATFORM), Darwin)
	TARGET      = lib$(NAME).dylib
endif
ifeq ($(PLATFORM), LINUX)
	TARGET      = lib$(NAME).so
endif
ifeq ($(PLATFORM), WIN32)
	TARGET      = lib$(NAME).dll
endif

all: $(TARGET)

lib$(NAME).so.$(VERSION) lib$(NAME).dylib lib$(NAME).dll: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

lib$(NAME).so.$(MAJOR) lib$(NAME).so: lib$(NAME).so.$(VERSION)
	@ln -sf $^ $@

clean:
	rm -rf $(TARGET) $(OBJS) lib$(NAME)*

install: $(TARGET)
	@cp -avf $(TARGET) $(PREFIX)/lib
ifeq ($(PLATFORM), LINUX)
	@cp -avf lib$(NAME).so.$(MAJOR) lib$(NAME).so $(PREFIX)/lib
endif
