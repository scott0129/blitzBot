EXENAME = blitzbot
OBJS = main.o Blitzbot.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ 
#LIBS = `pkg-config opencv --libs`
LIBS = ``

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME) $(LIBS)

main.o : main.cpp Blitzbot.h
	$(CXX) $(CXXFLAGS) main.cpp 

Blitzbot.o : Blitzbot.cpp Blitzbot.h
	$(CXX) $(CXXFLAGS) Blitzbot.cpp $(LIBS)
