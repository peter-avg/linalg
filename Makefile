.PHONY: all config build set-style format tidy test coverage

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
	rm -rf build coverage_report && rm .clang-format coverage.info

bench: build
	./build/run_benchmarks

docs: build
	doxygen

coverage: build test
	lcov --capture \
     --directory ./build \
     --ignore-errors inconsistent,inconsistent \
     --ignore-errors unsupported,unsupported \
     --ignore-errors format \
     --output-file coverage.info
	lcov --extract coverage.info \
		 "*/linalg/include/*" \
		 "*/linalg/src/*" \
		 "*/linalg/tests/*" \
		 --ignore-errors inconsistent,inconsistent \
		 --ignore-errors format \
		 --output-file coverage.info
	genhtml coverage.info \
			--ignore-errors inconsistent,inconsistent \
			--ignore-errors unsupported,unsupported \
			--ignore-errors category,category \
			--ignore-errors format \
			--output-directory coverage_report
	open coverage_report/index.html
