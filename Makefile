CC = gcc -c -x c
CFLAGS = -std=gnu11 -Wall -Werror -Iinclude -Isrc -include header.h
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
AS_EXEC = $(addprefix main/,$(1))
AS_TEST = $(addprefix $(DIR_TEST)/,$(1))
PREPOST = $(addprefix $(2),$(addsuffix $(3),$(1)))
AS_SRC = $(call PREPOST,$(1),$(DIR_SRC)/,.c)
AS_OBJ = $(call PREPOST,$(1),$(DIR_BUILD)/,.o)

FROM_SRC = $(subst .c,,$(subst $(DIR_SRC)/,,$(wildcard $(call AS_SRC,$(1)))))
HEADERS = $(wildcard include/*.h)
MODULES = $(call FROM_SRC,*)
OBJECTS = $(call AS_OBJ,$(MODULES))
LIBCMOCKA_ELF = $(call IN_BUILD,libcmocka_elf.a)
MAINS = $(call FROM_SRC,$(call AS_EXEC,*))
EXECS = $(call IN_BUILD,$(MAINS))
TESTMODS = $(call FROM_SRC,$(call AS_TEST,*))
TESTOBJS = $(call AS_OBJ,$(TESTMODS))
LIBTEST = $(call IN_BUILD,libtest.a)


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

.PHONY: test
test:
	$(MAKE) testconfig CONFIG=debug

.PHONY: testconfig
testconfig: buildconfig
	./$(call IN_BUILD,$(call AS_EXEC,runtests))

.PHONY: testall
testall:
	$(MAKE) testconfig CONFIG=debug
	$(MAKE) testconfig CONFIG=release


$(LIBCMOCKA_ELF): $(OBJECTS)
	$(AR) cr $@ $?
	ranlib $@

$(LIBTEST): $(TESTOBJS) $(LIBCMOCKA_ELF)
	$(AR) cr $@ $(TESTOBJS)
	ranlib $@

$(EXECS): $(LIBCMOCKA_ELF)

$(call IN_BUILD,%): $(call AS_OBJ,%)
	$(LD) -o $@ $(LDFLAGS) $< $(LIBS)
ifdef DO_STRIP
	strip $@
endif

$(call IN_BUILD,$(call AS_EXEC,runtests)): $(LIBTEST)
$(call IN_BUILD,$(call AS_EXEC,runtests)): LIBS := $(LIBTEST) $(LIBCMOCKA_ELF) -lcmocka $(LIBS)
$(call IN_BUILD,$(call AS_EXEC,runtests)): LDFLAGS += -Wl,--wrap=free

$(call AS_OBJ,%): $(call AS_SRC,%) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $<

$(call AS_OBJ,$(call AS_TEST,%)): CFLAGS += -include src/test/header.h -DTEST_NAME

