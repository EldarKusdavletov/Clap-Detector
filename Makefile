SANFLAGS = -fsanitize=address
CXXFLAGS += -Wall -g -std=c++17 $(SANFLAGS)
LDFLAGS += $(SANFLAGS)
main:	assignment.o wav-file.o
	$(CXX) -o $@ $^ $(SANFLAGS)
