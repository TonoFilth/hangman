# COMPILER
CC:=g++
CFLAGS:=-Wall -ggdb -std=c++11

# APP
APPNAME:=hangman

# APP DIRECTORIES
BUILDDIR:=bin
INCLUDEDIR:=include
LIBDIR:=lib
SRCDIR:=src
TMPDIR:=.obj

# SOURCES
MAINFILE=$(SRCDIR)/main.cpp
SOURCES:=$(shell find $(SRCDIR) -name '*.cpp')
_SOURCESFOLDERS:=$(shell find $(SRCDIR) -type d)
SOURCESFOLDERS:=$(subst ./,,$(_SOURCESFOLDERS))

# OBJECTS
_OBJECTS:=$(addprefix $(TMPDIR)/,$(SOURCES:%.cpp=%.o))
_OBJECTS:=$(subst ./,,$(_OBJECTS))
OBJECTS:=$(subst $(TMPDIR)/$(SRCDIR)/main.o,,$(_OBJECTS))

# EXTERNAL DEPENDENCIES
EXTDIR:=3rdParty
EXTHEADERS:=$(EXTDIR)
EXTHEADERS:=$(addprefix -I,$(EXTHEADERS))
EXTSOURCES:=$(shell find ./$(EXTDIR)/ -name '*.cpp' -o -name '*.c')
EXTOBJECTS:=$(subst ./,,$(EXTSOURCES))
EXTOBJECTS:=$(subst .cpp,.o,$(EXTOBJECTS))
EXTOBJECTS:=$(subst .c,.o,$(EXTOBJECTS))
EXTOBJECTS:=$(addprefix $(TMPDIR)/,$(EXTOBJECTS))

# EXTERNAL LIBRARIES
_EXTLIBS:=sfml-graphics sfml-window sfml-system sqlite3 kompex-sqlite-wrapper
EXTLIBS:=$(addprefix -l,$(_EXTLIBS))

# TESTS
TESTDIR:=test
TMPTESTDIR:=.obj_test
TESTMAINFILE:=$(TESTDIR)/main.cpp
TESTOUTPUTFILE:=test-runner

TESTSOURCES:=$(shell find $(TESTDIR) -name '*.cpp')
TESTSOURCES:=$(subst $(TESTMAINFILE),,$(TESTSOURCES))
_TESTSOURCESFOLDERS:=$(shell find $(TESTDIR) -type d)
TESTSOURCESFOLDERS:=$(subst ./,,$(_TESTSOURCESFOLDERS))

_TESTOBJECTS:=$(addprefix $(TMPTESTDIR)/,$(TESTSOURCES:%.cpp=%.o))
TESTOBJECTS:=$(subst ./,,$(_TESTOBJECTS))

_TESTEXTLIBS:=cppunit sfml-graphics sfml-window sfml-system sqlite3 kompex-sqlite-wrapper
TESTEXTLIBS:=$(addprefix -l,$(_TESTEXTLIBS))

# ================================== COMPILE ===================================
all: check $(OBJECTS) $(EXTOBJECTS) $(MAINFILE)
	@echo "========================="
	@echo " Building $(APPNAME) ..."
	@echo "========================="
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(EXTHEADERS) $(MAINFILE) $(OBJECTS) $(EXTOBJECTS) $(EXTLIBS) -o $(BUILDDIR)/$(APPNAME)

$(TMPDIR)/%.o: %.cpp
	@echo "------------------------"
	@echo "> COMPILING $< ..."
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(EXTHEADERS) $< -c -o $@

$(TMPDIR)/%.o: %.c
	@echo "------------------------"
	@echo "> COMPILING $< ..."
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(EXTHEADERS) $< -c -o $@

check:
	@test -d $(BUILDDIR) || mkdir $(BUILDDIR)
	@$(shell find $(SRCDIR) -depth -type d -print | cpio -pd $(TMPDIR))
	@$(shell find $(EXTDIR) -depth -type d -print | cpio -pd $(TMPDIR))

# =================================== TEST =====================================
check-test:
	@echo "Checking test dirs ..."
	@test -d $(TESTDIR) || { echo "The directory '$(TESTDIR)' doesn't exists. No tests to run."; exit 1; }
	@test -d $(TMPTESTDIR) || mkdir $(TMPTESTDIR)
	@$(shell find $(TESTSRCDIR) -depth -type d -print | cpio -pd $(TMPTESTDIR))

$(TMPTESTDIR)/%.o: %.cpp
	@echo "------------------------"
	@echo "> COMPILING $< ..."
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -I$(TESTDIR) $< -c -o $@

test: all check-test $(TESTOBJECTS)
	@echo "==============================="
	@echo "> Building $(APPNAME) tests ..."
	@echo "==============================="
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -I$(TESTDIR) $(EXTHEADERS) $(TESTMAINFILE) $(OBJECTS) $(EXTOBJECTS) $(EXTLIBS) $(TESTOBJECTS) $(TESTEXTLIBS) -o $(TESTDIR)/$(TESTOUTPUTFILE)
	./$(TESTDIR)/$(TESTOUTPUTFILE)

# =================================== OTHER ====================================
clean:
	-rm -Rf $(TMPDIR)
	-rm -Rf $(TMPTESTDIR)

.PHONY: clean all
