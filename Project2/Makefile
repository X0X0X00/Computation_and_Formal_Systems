#
# File: Makefile
# Creator: George Ferguson
# Created: Wed Sep 28 13:23:07 2022
# Time-stamp: <Wed Sep 28 13:37:43 EDT 2022 ferguson>
#

CFLAGS = -std=c99 -Wall -Werror

PROGRAMS = focs_11_27 focs_11_27_gf

all: $(PROGRAMS)

clean:
	-rm $(PROGRAMS)

ZIPBASE = focs_11_27

zip:
	mkdir $(ZIPBASE)
	cp -p $(PROGRAMS:%=%.c) Makefile $(ZIPBASE)
	zip -r $(ZIPBASE).zip $(ZIPBASE)
	rm -r $(ZIPBASE)


