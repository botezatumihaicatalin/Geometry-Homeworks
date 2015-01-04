CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		main.o camera.o vertex2.o vertex3.o model.o

LIBS =		-lGL -lGLU -lglut

TARGET =	3DHome

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
