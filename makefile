CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = loadbalancer.exe

OBJECTS = main.o Request.o Webserver.o Loadbalancer.o

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.cpp Loadbalancer.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Request.o: Request.cpp Request.h
	$(CXX) $(CXXFLAGS) -c Request.cpp

Webserver.o: Webserver.cpp Webserver.h Request.h
	$(CXX) $(CXXFLAGS) -c Webserver.cpp

Loadbalancer.o: Loadbalancer.cpp Loadbalancer.h Webserver.h Request.h
	$(CXX) $(CXXFLAGS) -c Loadbalancer.cpp

run: $(TARGET)
	./$(TARGET)

docs:
	doxygen Doxyfile

clean:
	rm -f $(OBJECTS) $(TARGET)

clean-docs:
	rm -rf docs