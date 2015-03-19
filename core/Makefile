CONFPATH     = ../
include $(CONFPATH)/config.mk

NAME        := image_core
MAJOR       := 0
MINOR       := 1
VERSION     := $(MAJOR).$(MINOR).1

CXXFLAGS    += -fPIC
CPPFLAGS    += -I$(THIRD_PARTY_PREFIX)/include/GraphicsMagick -I$(THIRD_PARTY_PREFIX)/include/
ifeq ($(PLATFORM), Darwin)
    LDFLAGS     += -shared -Wl,-install_name,lib$(NAME).so.$(MAJOR)
else
    LDFLAGS     += -shared -Wl,-soname,lib$(NAME).so.$(MAJOR)
endif
LDFLAGS += -L./ -L$(THIRD_PARTY_PREFIX)/lib -L/opt/lib -L/opt/lib/ -L/usr/X11/lib -L/opt/X11/lib -L/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/usr/lib
LIBS        = -lGraphicsMagick++ -lGraphicsMagick -lfreetype -lpng15 -lXext -lSM -lICE -lX11 -lbz2 -lxml2 -lz -lm -lpthread
OBJS        = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET      = lib$(NAME).so lib$(NAME).so.$(MAJOR) lib$(NAME).so.$(VERSION)

all: $(TARGET)

lib$(NAME).so.$(VERSION): $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

lib$(NAME).so.$(MAJOR) lib$(NAME).so: lib$(NAME).so.$(VERSION)
	@ln -sf $^ $@

clean:
	rm -rf $(TARGET) $(OBJS) lib$(NAME).so.*

install: $(TARGET)
	#$(INSTALL) $(INSTALLFLAGS) -t $(CONFPATH)/lib lib$(NAME).so.$(VERSION)
	@cp -avf lib$(NAME).so.$(MAJOR) lib$(NAME).so $(PREFIX)/lib/
