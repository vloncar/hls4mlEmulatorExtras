CPP_STANDARD := c++17
CXXFLAGS := -O3 -fPIC -std=$(CPP_STANDARD)

.PHONY: clean

emulator_interface.so: emulator.h
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

clean:
	rm emulator_interface.so