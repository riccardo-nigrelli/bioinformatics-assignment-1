CFLAGS+=-Wall -Wextra -std=c11 -pedantic -I"$(PWD)/include"

export CFLAGS

.PHONY: all apps bin clean test

all: bin apps test

bin:
	cd bin && $(MAKE) all

apps: bin
	cd app && $(MAKE) all

test: bin
	cd test && $(MAKE) all

clean:
	cd bin && $(MAKE) clean
	cd app && $(MAKE) clean
	cd test && $(MAKE) clean
