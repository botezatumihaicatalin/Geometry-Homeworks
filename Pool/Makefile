CXXFLAGS =	-O2 -g -Wall -std=c++11 -fmessage-length=0

OBJS = main.o circle.o scene.o segment.o vector2D.o point2D.o ball.o

LIBS = -lGL -lGLU -lglut

TARGET = Pool 

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
