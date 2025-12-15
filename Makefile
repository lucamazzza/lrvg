MAKE = make

all: build_engine_release build_engine_debug build_client_release build_client_debug

debug: build_engine_debug build_client_debug

release: build_engine_release build_client_release

package: release
	@echo "Creating release package..."
	@mkdir -p build/hanoi
ifeq ($(shell uname -s),Darwin)
	@cp bin/Release/libengine.dylib build/hanoi/
	@cp client/bin/Release/client build/hanoi/hanoi
else ifeq ($(OS),Windows_NT)
	@cp bin/Release/engine.dll build/hanoi/
	@cp client/bin/Release/client.exe build/hanoi/hanoi.exe
else
	@cp bin/Release/libengine.so build/hanoi/
	@cp client/bin/Release/client build/hanoi/hanoi
endif
	@cp client/*.ovo build/hanoi/ 2>/dev/null || true
	@cp client/*.dds build/hanoi/ 2>/dev/null || true
	@cp README_PACKAGE.txt build/hanoi/README.txt 2>/dev/null || true
	@echo "Fixing library paths..."
ifeq ($(shell uname -s),Darwin)
	@install_name_tool -change ../bin/Release/libengine.dylib @executable_path/libengine.dylib build/hanoi/hanoi
	@install_name_tool -id @executable_path/libengine.dylib build/hanoi/libengine.dylib
else ifeq ($(OS),Windows_NT)
	@echo "Windows package - no path fixing needed"
else
	@patchelf --set-rpath '$$ORIGIN' build/hanoi/hanoi 2>/dev/null || echo "patchelf not available, skipping rpath fix"
endif
	@echo "Creating tarball..."
	@cd build && tar -czf hanoi.tar.gz hanoi
	@rm -rf build/hanoi
	@echo "Package created at: build/hanoi.tar.gz"

build_engine_release: 
	$(MAKE) -C engine release

build_client_release: build_engine_release
	$(MAKE) -C client release

build_engine_debug:
	$(MAKE) -C engine debug

build_client_debug: build_engine_debug
	$(MAKE) -C client debug

build_engine_all: 
	$(MAKE) -C engine all

build_client_all: build_engine
	$(MAKE) -C client all

clean: clean_engine clean_client clean_package

clean_engine: 
	$(MAKE) -C engine clean

clean_client: 
	$(MAKE) -C client clean

clean_package:
	rm -rf build

test: build_engine_debug
	$(MAKE) -C engine test

.PHONY: clean_engine clean_client clean_package test package
