CXXFLAGS =	-O2 -g -Wall -std=c++11 -fmessage-length=0

OBJS = main.o circle.o scene.o segment.o vector2D.o point2D.o ball.o cue.o constants.o 

LIBS = -lglut32 -lglu32 -lopengl32

TARGET = Pool.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
