.PHONY: all config build set-style format tidy test

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    TIDY_EXTRA = --extra-arg=--stdlib=libc++ \
                 --extra-arg=-Wno-error
else
    TIDY_EXTRA =
endif

config: 
	cmake -S . -B build

build: config
	cmake --build build 

set-style:
	@clang-format --style=Google --dump-config > .clang-format

format: set-style
	@find src include tests \( -name "*.cpp" -o -name "*.hpp" \) \
		| xargs clang-format -i

tidy: build
	find src -name "*.cpp" | xargs clang-tidy -p build $(TIDY_EXTRA)

test: build
	ctest --test-dir build --output-on-failure

clean:
	rm -rf build && rm .clang-tidy .clang-format

bench: build
	./build/run_benchmarks

docs: build
	doxygen
