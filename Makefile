CPP_STANDARD := c++17
CXXFLAGS := -O3 -fPIC -std=$(CPP_STANDARD)
ifeq ($(strip $(PREFIX)),)
PREFIX:=.
endif

.DEFAULT_GOAL := all
.PHONY: clean all install

HLS4ML_INCLUDE := include/hls4ml/
INCLUDES := -I$(HLS4ML_INCLUDE)

EMULATOR_LIB:=libemulator_interface.so
all: $(EMULATOR_LIB)
	@echo All done

install: all
	@rm -rf $(PREFIX)/lib64
	@mkdir -p $(PREFIX)/lib64
	cp $(EMULATOR_LIB) $(PREFIX)/lib64

$(EMULATOR_LIB): src/hls4ml/emulator.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -shared $^ -o $@

clean:
	rm $(EMULATOR_LIB)
