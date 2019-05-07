CFLAGS+=-Wall -Wextra -ansi -pedantic -I"$(PWD)/include" # -I/usr/include/python2.7 -lpython2.7

export CFLAGS

.PHONY: all apps bin clean

all: bin apps

bin:
	cd bin && $(MAKE) all

apps: bin
	cd app && $(MAKE) all

clean:
	cd bin && $(MAKE) clean
	cd app && $(MAKE) clean
