CPP_STANDARD := c++17
CXXFLAGS := -O3 -fPIC -std=$(CPP_STANDARD)
ifeq ($(strip $(PREFIX)),)
PREFIX:=.
endif

.DEFAULT_GOAL := all
.PHONY: clean all install

EMULATOR_LIB:=libemulator_interface.so
all: $(EMULATOR_LIB)
	@echo All done

install: all
	@rm -rf $(PREFIX)/include $(PREFIX)/lib64
	@mkdir -p $(PREFIX)/include $(PREFIX)/lib64
	cp emulator.h $(PREFIX)/include/
	cp -r ap_types $(PREFIX)/include/
	cp $(EMULATOR_LIB) $(PREFIX)/lib64

$(EMULATOR_LIB): emulator.cc emulator.h
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

clean:
	rm $(EMULATOR_LIB)
