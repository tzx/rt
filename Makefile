release:
	cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
	cmake --build ./build --config Release --target all

debug:
	cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug
	cmake --build ./build --config Debug --target all

all:
	$(MAKE) release
