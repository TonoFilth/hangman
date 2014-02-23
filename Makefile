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
_EXTLIBS:=sfml-graphics sfml-window sfml-system
EXTLIBS:=$(addprefix -l,$(_EXTLIBS))

# ================================== COMPILE ===================================
all: check $(OBJECTS) $(EXTOBJECTS) $(MAINFILE)
	@echo "========================="
	@echo " Building $(APPNAME) ..."
	@echo "========================="
	@echo $(EXTOBJECTS)
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

# =================================== OTHER ====================================
clean:
	-rm -Rf $(TMPDIR)
	-rm -Rf $(TMPTESTDIR)

.PHONY: clean all
