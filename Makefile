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

DIR_BASE = build
DIR_SRC = src
DIR_TEST = test
IN_BUILD = $(addprefix $(DIR_BUILD)/,$(1))
AS_TEST = $(addprefix $(DIR_TEST)/,$(1))
PREPOST = $(addprefix $(2),$(addsuffix $(3),$(1)))
AS_SRC = $(call PREPOST,$(1),$(DIR_SRC)/,.c)
AS_OBJ = $(call PREPOST,$(1),$(DIR_BUILD)/,.o)
AS_TMP_SRC = $(call PREPOST,$(1),$(DIR_BUILD)/,.c)

FROM_SRC = $(subst .c,,$(subst $(DIR_SRC)/,,$(wildcard $(call AS_SRC,$(1)))))
MODULES = $(call FROM_SRC,*)
MKCTEST = $(call IN_BUILD,mkctest)
RUNCTESTS = $(call IN_BUILD,runctests)
LIBCTESTS = $(call IN_BUILD,libctests.a)
TESTMODS = $(call FROM_SRC,$(call AS_TEST,*))
TESTS = $(call IN_BUILD,$(TESTMODS))

OBJECTS = $(call AS_OBJ,$(MODULES))


.SECONDARY:

.PHONY: buildall
buildall:
	$(MAKE) buildconfig CONFIG=debug
	$(MAKE) buildconfig CONFIG=release

.PHONY: buildconfig
buildconfig:
	@echo ==== Config: $(CONFIG) ====
	mkdir -p $(DIR_BUILD)/$(DIR_TEST) $(DIR_BUILD)/main
	$(MAKE) $(RUNCTESTS) $(LIBCTESTS) $(TESTS)

.PHONY: clean
clean:
	rm -rf $(DIR_BASE)

.PHONY: run
run:
	$(MAKE)
	./$(RUNCTESTS) $(ARGS) ; echo Exit code: $$?

.PHONY: debug
debug:
	$(MAKE)
	gdb $(RUNCTESTS)


$(RUNCTESTS): $(call AS_OBJ,main/runctests) $(LIBCTESTS)
	$(LD) -o $@ $(LDFLAGS) $? $(LIBS)
ifdef DO_STRIP
	strip $@
endif

$(LIBCTESTS): $(OBJECTS)
	$(AR) cr $@ $?
	ranlib $@

$(call AS_OBJ,%): $(call AS_SRC,%)
	$(CC) -o $@ $(CFLAGS) $<

$(call IN_BUILD,$(call AS_TEST,%)): $(call AS_OBJ,$(call AS_TEST,%)) $(LIBCTESTS)
	@echo $<
	touch $@


# EOF
