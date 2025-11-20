MAKE = make

all: build_engine_release build_engine_debug build_client_release build_client_debug

debug: build_engine_debug build_client_debug

release: build_engine_release build_client_release

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

clean: clean_engine clean_client

clean_engine: 
	$(MAKE) -C engine clean

clean_client: 
	$(MAKE) -C client clean

.PHONY: clean_engine clean_client
