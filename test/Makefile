CXX	= g++
CXXFLAGS= -g -std=c++14

TEST	= window.elf

%.elf : %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ ../tui.a

default:
	make $(TEST)
	./$(TEST)

clean:
	rm -f *.o
	rm -f *.elf
