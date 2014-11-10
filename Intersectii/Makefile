CXXFLAGS =	-O2 -g -Wall -std=c++11 -fmessage-length=0

OBJS = main.o scene.o segment.o vector2D.o point2D.o

LIBS = -lGL -lGLU -lglut

TARGET = Intersectii 

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
