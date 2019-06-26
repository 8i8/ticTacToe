srcdir	= src/
#objdir	= $(srcdir)
objdir	= build/
exedir	=

EXE	= $(exedir)ticTacToe

SRCS	= $(srcdir)draw.c $(srcdir)logic.c $(srcdir)main.c
OBJS	= $(SRCS:$(srcdir)%.c=$(objdir)%.o)
OUTDIRS	= $(dir $(objdir) $(exedir))

# Enable Debian/Ubuntu build hardening unless already
# enabled/disabled  — see hardened-cc(1) —  and ensure
# the setting, whatever it is, is seen by the compiler
# (and linker, hardened-ld(1)).
DEB_BUILD_HARDENING ?= 1
export DEB_BUILD_HARDENING

CC	= gcc

CFLAGS	= -Wextra -Wall -pedantic
CFLAGS	+= -Wstrict-prototypes
#CFLAGS	+= -O
CFLAGS	+= -g

.PHONY:	all clean distclean
all:	$(EXE)

clean:
	rm -f -- $(OBJS)

distclean: clean
	rm -f -- $(EXE)
	-rmdir --ignore-fail-on-non-empty -- $(OUTDIRS)

$(EXE):	$(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJS): $(srcdir)ticTacToe.h Makefile | $(OUTDIRS)

# When srcdir == objdir, make's default implicit rule works fine.
# However, when srcdir ≠ objdir, it never matches, because (e.g.,
# with `make objdir=foo- ...') foo-draw.o differs not just in the
# suffix (.c → .o) but also in the prefix (src/ → foo-).  Hence,
# we redefine the implicit rule to also work in that situation.
$(objdir)%.o: $(srcdir)%.c
	$(CC) -c $(CFLAGS) $< -o $@

%/:
	mkdir -p -- $@
