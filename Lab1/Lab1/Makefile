CC=g++
CFLAGS=-c -D_LINUX
LDFLAGS=
SOURCES=../core/src/IApplication_linux.cpp ../core/src/IRenderer.cpp ../core/src/OpenGLRenderer.cpp ../core/src/Timer.cpp ../core/src/IGraphNode.cpp main.cpp TheApp.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=LAB1
INCLUDE=
LIBS =  -L /usr/X11R6/lib/ -lGL -lGLU -lX11 -lXi -lm
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(INCLUDE) $@

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)
