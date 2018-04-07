CXX	= g++
CXXFLAGS= -g -std=c++11

TEST	= password.elf

%.elf : %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ ../tui.a

default:
	make $(TEST)
	./$(TEST)
