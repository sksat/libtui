CXX	= g++
CXXFLAGS= -g -std=c++14

TEST	= keyboard.elf

%.elf : %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ ../tui.a

default:
	make $(TEST)
	./$(TEST)
