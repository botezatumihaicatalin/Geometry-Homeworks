CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		ShadersGLEW.o TwoColorsShading.o HotColdShading.o GoraudShading.o AbstractRenderingContext.o

LIBS =		-lglew32 -lfreeglut -lglu32 -lopengl32

TARGET =	ShadersGLEW.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
