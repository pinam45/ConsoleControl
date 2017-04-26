 #########################################################################################
 #                                                                                       #
 # PFC, pinam45 functions and classes                                                    #
 # Copyright (C) 2016 PINARD Maxime (maxime.pin@live.fr)                                 #
 #                                                                                       #
 # This software is provided 'as-is', WITHOUT ANY EXPRESS OR IMPLIED WARRANTY.           #
 # In NO EVENT will the authors be held liable for any damages arising from the          #
 # use of this software.                                                                 #
 #                                                                                       #
 # Permission is granted to anyone to use this software for any purpose,                 #
 # including commercial applications, and to alter it and redistribute it freely,        #
 # subject to the following restrictions:                                                #
 #                                                                                       #
 # 1. The origin of this software must not be misrepresented;                            #
 # you must not claim that you wrote the original software.                              #
 # If you use this software in a product, an acknowledgment                              #
 # in the product documentation would be appreciated but is not required.                #
 #                                                                                       #
 # 2. Altered source versions must be plainly marked as such,                            #
 # and must not be misrepresented as being the original software.                        #
 #                                                                                       #
 # 3. This notice may not be removed or altered from any source distribution.            #
 #                                                                                       #
 #########################################################################################

#=============================================================================
# Project related variables
EXENAME           = ConsoleControlExamples
LIBNAME           = ConsoleControl
FILEIDENTIFIER    = .c
COMPILER          = gcc
COMPFLAGS         = -pedantic -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion -Wextra -Wfloat-equal -Wformat -Winit-self -Winvalid-pch -Wlogical-op -Wmain -Wmissing-declarations -Wmissing-include-dirs -Wpointer-arith -Wredundant-decls -Wshadow -Wswitch-default -Wswitch-enum -Wundef -Wuninitialized -Wunreachable-code -Wwrite-strings
COMPSTANDARD      = -std=c11
EXELINKS          = -lConsoleControl -lm
LIBLINKS          =
DBARGS            = -g -DDEBUG -DLOGGER_ENABLED

BUILDDIR          = build/
BINARY_OUTPUT_DIR = $(BUILDDIR)bin/
LIB_OUTPUT_DIR    = $(BUILDDIR)lib/
OBJDIR            = $(BUILDDIR)obj/
EXESOURCEDIRS     = Examples/src/
LIBSOURCEDIRS     = ConsoleControl/src/
INCLUDEDIRS       = /usr/include/ ConsoleControl/include/ Logger/include/ Examples/include/
LIBSDIRS          = /usr/lib/ $(LIB_OUTPUT_DIR)


#=============================================================================
# Commands variables
DISPLAY           = printf
MKDIR             = mkdir -p
RMDIR             = rmdir
RM                = rm -f
LD                = ld -r
AR                = ar rcs


#=============================================================================
# Other
VOIDECHO          = > /dev/null 2>&1


#=============================================================================
# Semi-automatic variables
EXEFINALOBJ       = $(OBJDIR)$(EXENAME).o
EXEFINAL          = $(BINARY_OUTPUT_DIR)$(EXENAME).elf
LIBFINAL          = $(LIB_OUTPUT_DIR)lib$(LIBNAME).a
INCLUDEARGS       = $(addprefix -I,$(INCLUDEDIRS))
LIBARGS           = $(addprefix -L,$(LIBSDIRS))


#=============================================================================
# Automatic variables
EXESOURCES        = $(foreach sourcedir,$(EXESOURCEDIRS),$(wildcard $(sourcedir)**/*$(FILEIDENTIFIER)) $(wildcard $(sourcedir)*$(FILEIDENTIFIER)))
LIBSOURCES        = $(foreach sourcedir,$(LIBSOURCEDIRS),$(wildcard $(sourcedir)**/*$(FILEIDENTIFIER)) $(wildcard $(sourcedir)*$(FILEIDENTIFIER)))
EXEOBJECTS        = $(patsubst %$(FILEIDENTIFIER),%.o,$(foreach sourcedir,$(EXESOURCEDIRS),$(subst $(sourcedir),$(OBJDIR),$(wildcard $(sourcedir)**/*$(FILEIDENTIFIER)) $(wildcard $(sourcedir)*$(FILEIDENTIFIER)))))
LIBOBJECTS        = $(patsubst %$(FILEIDENTIFIER),%.o,$(foreach sourcedir,$(LIBSOURCEDIRS),$(subst $(sourcedir),$(OBJDIR),$(wildcard $(sourcedir)**/*$(FILEIDENTIFIER)) $(wildcard $(sourcedir)*$(FILEIDENTIFIER)))))
GENERATED_FILES   = $(LIBOBJECTS) $(EXEOBJECTS) $(EXEFINALOBJ) $(LIBFINAL) $(EXEFINAL)
GENERATED_FOLDERS = $(OBJDIR) $(BINARY_OUTPUT_DIR) $(LIB_OUTPUT_DIR) $(BUILDDIR)


#=============================================================================
# Special GNU make variables
VPATH             = $(EXESOURCEDIRS) $(LIBSOURCEDIRS)


#=============================================================================
# Rules: Phony Targets
.PHONY: silent
silent:
	@make --silent $(EXEFINAL)

.PHONY: all
all: $(EXEFINAL)

.PHONY: debug
debug: COMPFLAGS += $(DBARGS)
debug: all

.PHONY: $(LIBNAME)
$(LIBNAME): $(LIBFINAL)

.PHONY: lib
lib: $(LIBFINAL)

.PHONY: $(EXENAME)
$(EXENAME): $(EXEFINAL)

.PHONY: tests
tests: $(EXEFINAL)

.PHONY: clean
clean:
	@$(DISPLAY) "\n\033[1;32m->\033[0m Cleaning files...\n"
	@$(DISPLAY) " $(foreach file,$(GENERATED_FILES),$(if $(wildcard $(file)),\033[1;32m-\033[0m Removing file \033[0;33m$(file)\033[0m\n,\b))"
	@$(RM) $(GENERATED_FILES)
	@$(DISPLAY) "\n\033[1;32m->\033[0m Cleaning folders...\n"
	@$(DISPLAY) " $(foreach folder,$(GENERATED_FOLDERS),$(if $(wildcard $(folder)),\033[1;32m-\033[0m Removing folder \033[0;33m$(folder)\033[0m\n,\b))"
	@$(RMDIR) $(GENERATED_FOLDERS) $(VOIDECHO) || true
	@$(DISPLAY) "\n"

.PHONY : help
help:
	@$(DISPLAY) "\n\033[1;32m->\033[0m Valid targets:\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m silent                    \033[0m Default if no target is provided, equivalent to: make --silent all\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m all                       \033[0m Build $(LIBNAME) and $(EXENAME)\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m lib                       \033[0m Build $(LIBNAME)\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m tests                     \033[0m Build $(EXENAME)\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m debug                     \033[0m All with debug symbols\n"
	@$(DISPLAY) " \033[1;32m-\033[1;34m clean                     \033[0m Remove files and folders generated by the makefile\n"
	@$(DISPLAY) "\n"


#=============================================================================
# Rules: File Targets
$(EXEFINAL): $(EXEFINALOBJ) $(LIBFINAL)
	@$(DISPLAY) "\n\033[0m\033[1;34m[··]\033[0m Building \033[0;33m$@\033[0m from \033[0;33m$^\033[0m...   "
	@$(MKDIR) $(BINARY_OUTPUT_DIR)
	$(COMPILER) $(EXEFINALOBJ) -o $@ $(LIBARGS) $(EXELINKS)
	@$(DISPLAY) "\r\033[1C\033[1;32mOK\033[0m"
	@$(DISPLAY) "\n\n"

$(LIBFINAL): $(LIBOBJECTS)
	@$(DISPLAY) "\n\033[0m\033[1;34m[··]\033[0m Archiving objects files into \033[0;33m$@\033[0m...   "
	@$(MKDIR) $(LIB_OUTPUT_DIR)
	$(AR) $@ $(LIBOBJECTS)
	@$(DISPLAY) "\r\033[1C\033[1;32mOK\033[0m"

$(EXEFINALOBJ): $(EXEOBJECTS)
	@$(DISPLAY) "\n\033[0m\033[1;34m[··]\033[0m Merging objects files into \033[0;33m$@\033[0m...   "
	$(LD) $(EXEOBJECTS) -o $@
	@$(DISPLAY) "\r\033[1C\033[1;32mOK\033[0m"

$(OBJDIR)%.o: %$(FILEIDENTIFIER)
	@$(DISPLAY) "\n\033[0m\033[1;34m[··]\033[0m Building \033[0;33m$@\033[0m from \033[0;33m$^\033[0m...   "
	@$(MKDIR) $(OBJDIR)
	$(COMPILER) $(COMPFLAGS) $(COMPSTANDARD) $(INCLUDEARGS) -c $^ -o $@
	@$(DISPLAY) "\r\033[1C\033[1;32mOK\033[0m"
