CXX	= g++
CXXFLAGS= -g -std=c++14

TEST	= color.elf

%.elf : %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ ../tui.a

default:
	make $(TEST)
	./$(TEST)
