CC = gcc -c -x c
CFLAGS = -std=c11 -Wall -Werror -Iinclude -include header.h
LD = gcc -static
LDFLAGS =
LIBS = -lcmp -lm
CCLD = gcc -static
AR = ar
ifdef CONFIG
	include $(CONFIG).mak
else
	include debug.mak
endif

DIR_BASE = build
DIR_SRC = src
DIR_TEST = test
IN_BUILD = $(addprefix $(DIR_BUILD)/,$(1))
AS_EXEC = $(addprefix main/,$(1))
AS_TEST = $(addprefix $(DIR_TEST)/,$(1))
PREPOST = $(addprefix $(2),$(addsuffix $(3),$(1)))
AS_SRC = $(call PREPOST,$(1),$(DIR_SRC)/,.c)
AS_OBJ = $(call PREPOST,$(1),$(DIR_BUILD)/,.o)
AS_TMP_SRC = $(call PREPOST,$(1),$(DIR_BUILD)/,.c)

FROM_SRC = $(subst .c,,$(subst $(DIR_SRC)/,,$(wildcard $(call AS_SRC,$(1)))))
MODULES = $(call FROM_SRC,*)
OBJECTS = $(call AS_OBJ,$(MODULES))
LIBCTESTS = $(call IN_BUILD,libctests.a)
MAINS = $(call FROM_SRC,$(call AS_EXEC,*))
EXECS = $(call IN_BUILD,$(MAINS))
TESTMODS = $(call FROM_SRC,$(call AS_TEST,*))
TESTS = $(call IN_BUILD,$(TESTMODS))



.SECONDARY:

.PHONY: buildall
buildall:
	$(MAKE) buildconfig CONFIG=debug
	$(MAKE) buildconfig CONFIG=release

.PHONY: buildconfig
buildconfig:
	@echo ==== Config: $(CONFIG) ====
	mkdir -p $(DIR_BUILD)/$(DIR_TEST) $(DIR_BUILD)/main
	$(MAKE) $(EXECS) $(TESTS)

.PHONY: clean
clean:
	rm -rf $(DIR_BASE)


$(LIBCTESTS): $(OBJECTS)
	$(AR) cr $@ $?
	ranlib $@

$(EXECS) $(TESTS): $(LIBCTESTS)

$(call IN_BUILD,%): $(call AS_OBJ,%)
	$(LD) -o $@ $(LDFLAGS) $< \
		$(and $(filter $(call IN_BUILD,$(call AS_TEST,%)),$@),$(LIBCTESTS)) \
		$(LIBS)
ifdef DO_STRIP
	strip $@
endif

$(call AS_OBJ,%): $(call AS_SRC,%)
	$(CC) -o $@ $(CFLAGS) $<


# EOF
