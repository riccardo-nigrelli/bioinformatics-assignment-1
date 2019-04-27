LDFLAGS+=-L../bin
LDLIBS=-lbioinformatics_s -lm

apps_targets+=main

export LDFLAGS
export LDLIBS
export apps_targets

include mk/*.mk


.PHONY: all clean

all: $(apps_targets)

clean:
	$(RM) $(apps_targets) *.o
