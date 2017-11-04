DIR_BASE = build
DIR_SRC = src
MODULES_LIBCTESTS = hello
MODULES_RUNCTESTS = runctests

CC = gcc -c -x c -static
CFLAGS = -std=c11 -Wall -Werror -Iinclude
LD = gcc -static
LDFLAGS =
LIBS = -lm
CCLD = gcc -static
AR = ar
ifdef CONFIG
	include $(CONFIG).mak
else
	include debug.mak
endif

BUILDIZE = $(addprefix $(DIR_BUILD)/,$(1))
TARGET_RUNCTESTS = $(call BUILDIZE,runctests)
TARGET_LIBCTESTS = $(call BUILDIZE,libctests.a)

OBJECTIZE = $(call BUILDIZE,$(addsuffix .o,$(1)))
OBJECTS_RUNCTESTS = $(call OBJECTIZE,$(MODULES_RUNCTESTS))
OBJECTS_LIBCTESTS = $(call OBJECTIZE,$(MODULES_LIBCTESTS))

SRCIZE = $(addprefix $(DIR_SRC)/,$(1))


.PHONY: buildall
buildall:
	$(MAKE) buildconfig CONFIG=debug
	$(MAKE) buildconfig CONFIG=release

.PHONY: buildconfig
buildconfig:
	@echo ==== Config: $(CONFIG) ====
	mkdir -p $(DIR_BUILD)
	$(MAKE) $(TARGET_RUNCTESTS) $(TARGET_LIBCTESTS)

.PHONY: clean
clean:
	rm -rf $(DIR_BASE)

.PHONY: run
run:
	$(MAKE)
	$(TARGET_RUNCTESTS) $(ARGS) ; echo Exit code: $$?

.PHONY: debug
debug:
	$(MAKE)
	gdb $(TARGET_RUNCTESTS)


$(TARGET_RUNCTESTS): $(OBJECTS_RUNCTESTS) $(TARGET_LIBCTESTS)
	$(LD) -o $@ $(LDFLAGS) $? $(LIBS)
ifdef DO_STRIP
	strip $@
endif

$(TARGET_LIBCTESTS): $(OBJECTS_LIBCTESTS)
	$(AR) cr $@ $?
	ranlib $@

$(call OBJECTIZE,%): $(call SRCIZE,%.c)
	$(CC) -o $@ $(CFLAGS) $<


# EOF
