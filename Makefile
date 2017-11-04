DIR_BASE = build
MODULES_COMMON = hello
MODULES_RUNCTESTS = $(MODULES_COMMON) \
					runctests
MODULES_LIBCTESTS = $(MODULES_COMMON)

CC = gcc -c -x c
CFLAGS = -std=c11 -Wall -Werror
LD = gcc
LDFLAGS =
LIBS = -lm
AR = ar
ifdef CONFIG
	include $(CONFIG)
endif

BUILDIZE = $(addprefix $(DIR_BUILD)/,$(1))
TARGET_RUNCTESTS = $(call BUILDIZE,runctests)
TARGET_LIBCTESTS = $(call BUILDIZE,libctests.a)

OBJECTIZE = $(call BUILDIZE,$(addsuffix .o,$(1)))
OBJECTS_COMMON = $(call OBJECTIZE,$(MODULES_COMMON))
OBJECTS_RUNCTESTS = $(OBJECTS_COMMON) $(call OBJECTIZE,$(MODULES_RUNCTESTS))
OBJECTS_LIBCTESTS = $(OBJECTS_COMMON) $(call OBJECTIZE,$(MODULES_LIBCTESTS))


.PHONY: buildall
buildall:
	$(MAKE) buildconfig CONFIG=debug.mak
	$(MAKE) buildconfig CONFIG=release.mak

.PHONY: buildconfig
buildconfig:
	@echo ==== Config: $(subst .mak,,$(CONFIG)) ====
	mkdir -p $(DIR_BUILD)
	$(MAKE) $(TARGET_RUNCTESTS) $(TARGET_LIBCTESTS)

$(TARGET_RUNCTESTS): $(OBJECTS_RUNCTESTS) $(TARGET_LIBCTESTS)
	$(LD) -o $@ $(LDFLAGS) $? $(LIBS)
ifdef DO_STRIP
	strip $@
endif

$(TARGET_LIBCTESTS): $(OBJECTS_LIBCTESTS)
	$(AR) cr $@ $?
	ranlib $@

$(call OBJECTIZE,%): %.c
	$(CC) -o $@ $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf $(DIR_BASE)

# EOF
