LDFLAGS+=-L../bin
LDLIBS=-lbioinformatics_s -lm

test_targets+=test_bloom_filter

export LDFLAGS
export LDLIBS
export test_targets

include mk/*.mk


.PHONY: all clean

all: $(test_targets)

clean:
	$(RM) $(test_targets) *.o
