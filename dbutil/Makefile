# COMPILER
CC:=g++
CFLAGS:=-Wall -ggdb -std=c++11

# APP
APPNAME:=dbutil

# APP DIRECTORIES
BUILDDIR:=bin
INCLUDEDIR:=../include
LIBDIR:=../lib
SRCDIR:=../src
TMPDIR:=../.obj

# SOURCES
MAINFILE=dbutil.cpp
SOURCES:=$(shell find $(SRCDIR) -name '*.cpp')
SOURCES:=$(subst $(SRCDIR)/main.cpp,,$(SOURCES))

# OBJECTS
_OBJECTS:=$(addprefix $(TMPDIR)/,$(SOURCES:%.cpp=%.o))
_OBJECTS:=$(subst $(SRCDIR),src,$(_OBJECTS))
OBJECTS:=$(subst $(TMPDIR)/$(SRCDIR)/main.o,,$(_OBJECTS))

# EXTERNAL DEPENDENCIES
EXTDIR:=../3rdParty
EXTHEADERS:=$(EXTDIR)
EXTHEADERS:=$(addprefix -I,$(EXTHEADERS))
EXTSOURCES:=$(shell find ./$(EXTDIR)/ -name '*.cpp' -o -name '*.c')
EXTOBJECTS:=$(subst ../,,$(EXTSOURCES))
EXTOBJECTS:=$(subst .cpp,.o,$(EXTOBJECTS))
EXTOBJECTS:=$(subst .c,.o,$(EXTOBJECTS))
EXTOBJECTS:=$(addprefix $(TMPDIR)/,$(EXTOBJECTS))

# EXTERNAL LIBRARIES
_EXTLIBS:=sfml-graphics sfml-window sfml-system sqlite3 kompex-sqlite-wrapper
EXTLIBS:=$(addprefix -l,$(_EXTLIBS))

# ================================== COMPILE ===================================
all: check $(MAINFILE)
	@echo "========================="
	@echo " Building $(APPNAME) ..."
	@echo "========================="
	@echo $(OBJECTS)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(EXTHEADERS) $(MAINFILE) $(OBJECTS) $(EXTOBJECTS) $(EXTLIBS) -o $(BUILDDIR)/$(APPNAME)

check:
	@test -d $(BUILDDIR) || mkdir $(BUILDDIR)

.PHONY: clean all
