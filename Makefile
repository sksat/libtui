CXX	= g++
CXXFLAGS= -std=c++14 -g

TARGET	= tui.a
OBJS	= tui/config.o tui/keyboard.o tui/screen.o

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

default:
	make $(TARGET)
	make -C test

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	make -C test clean

$(TARGET) : $(OBJS)
	ar rcs $@ $(OBJS)

test: test.o tui.a
	$(CXX) test.o tui.a -o $@
