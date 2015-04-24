#***********************************************************************
#* Description:                                                        *
#* ------------                                                        *
#*                                                                     *
#* Author: Dr. Martin Ettl                                             *
#* Date  : 2011-09-15                                                  *
#*                                                                     *
#* LINUX-Makefile (gmake): Ubuntu linux                                *
#* Makefile to compile and build all necessary programms.              *
#*                                                                     *
#* Usage and basic features:                                           *
#*                                                                     *
#*  - make build  [creates the whole project]                          *
#*  - make clean  [removes all object and binary files]                *
#*  - make depend [detects header dependencies]                        *
#*  - make rpc    [generates files using idl2rpc]                      *
#*                                                                     *
#***********************************************************************

# ============================================================
# DEFINITIONS
# ============================================================

#######################################################################
# Determine the number cores of the machine, where the makefile is executed.
# This helps to set the -j option (from make), to speedup the build
# process of 'large' projects.  
NPROCS=1
OS:=$(shell uname -s)
ifeq ($(OS),Linux)
    NPROCS:=$(shell grep -c ^processor /proc/cpuinfo) 
endif
#######################################################################


BIN_DIR 	= ../bin
OBJ_DIR 	= ../obj
SRC_DIR 	= ../src
SRC_EXT_DIR 	= ../srcext
RPC_DIR 	= ../rpc
APP_NAME	= barnsley_fern
GNUPLOT_CPP 	= $(SRC_EXT_DIR)/gnuplot-cpp/gnuplot-cpp/

CXX 			= g++
CPP_INCLUDE_HEADER 	= -I$(GNUPLOT_CPP)
CPPCOMPILER_FLAGS 	= -O2 -W -Wall -Wunused -Wextra -ansi -pedantic -Wno-write-strings -fno-strict-aliasing $(CPP_INCLUDE_HEADER)
CPPCOMPILER_CALL 	= $(CXX) -c  $(CPPCOMPILER_FLAGS) -o $@ $< 

CC 			= gcc
CCOMPILER_FLAGS 	= -O2 -W -Wall -Wunused -Wextra -ansi -pedantic   
CCOMPILER_CALL  	= $(CC) -c $(CCOMPILER_FLAGS) -o $@ $< 

LINKER 			= $(CXX) 
LINKER_FLAGS 		= 
LINKER_CALL 		= $(LINKER) -o $@ $^ $(LINKER_FLAGS)


all: $(BIN_DIR)/$(APP_NAME)

# ============================================================
# LINKER-RULES
# ===========================================================
$(BIN_DIR)/$(APP_NAME) : $(OBJ_DIR)/$(APP_NAME).o
	$(LINKER_CALL)
# 
# ===========================================================
# c++ - SOURCES
# ===========================================================
SRCS = $(SRC_DIR)/$(APP_NAME).cpp


# ===========================================================
# c - SOURCES
# =========================================================== 
CSRCS = 

# ===========================================================
# SUPPORTING-RULES
# ===========================================================
build: mrproper depend 
	# after generating the dependencies it is necessary to call make again
	make -j$(NPROCS) all 

rpc:
	#not implemented
rpctest:
	#not implemented

clean:
	rm -f $(BIN_DIR)/*
	rm -f $(OBJ_DIR)/*

mrproper:
	rm -f $(BIN_DIR)/*
	rm -f $(OBJ_DIR)/*
	rm -f $(SRC_DIR)/*.bck

touch:
	@find $(SRC_DIR) -name "*.c*" -type f -exec touch {} \;
	@find $(SRC_EXT_DIR) -name "*.c*" -type f -exec touch {} \;
	@find $(RPC_DIR) -name "*.c*" -type f -exec touch {} \;

lib:
	#
install:
	#
prepare:
	#

depend:
	@cat < /dev/null > makedep
	@cat < /dev/null > cmakedep
# First C++
	@for i in ${SRCS}; do \
		 (echo $$i; $(CXX) $(CPPCOMPILER_FLAGS) -MM $$i >> makedep); done
#       Write full path information before each *.o-dependency
	@echo 's/.*\.o:/..\/obj\/&/g' > eddep
	@sed -f eddep makedep > makedep1
	@mv makedep1 makedep
	@rm eddep
#       Add the rule to each dependency
	@echo 'a' > eddep
	@echo '	$$(CPPCOMPILER_CALL)' >> eddep
	@echo '.' >> eddep
	@echo 'g/.*\.o:/i\' >> eddep
	@echo '	$$(CPPCOMPILER_CALL)\' >> eddep
	@echo '.' >> eddep
	@echo '1,1d' >> eddep
	@echo 'w' >> eddep
	@ed - makedep < eddep
	@rm eddep
# Then C
	@for i in ${CSRCS}; do \
		 (echo $$i; $(CC) $(CCOMPILER_FLAGS) -MM $$i >> cmakedep); done
#       Write full path information before each *.o-dependency
	@echo 's/.*\.o:/..\/obj\/&/g' > ceddep
	@sed -f ceddep cmakedep > cmakedep1
	@mv cmakedep1 cmakedep
	@rm ceddep
##       Add the rule to each dependency
	@echo 'a' > ceddep
	@echo '	$$(CCOMPILER_CALL)' >> ceddep
	@echo '.' >> ceddep
	@echo 'g/.*\.o:/i\' >> ceddep
	@echo '	$$(CCOMPILER_CALL)\' >> ceddep
	@echo '.' >> ceddep
	@echo '1,1d' >> ceddep
	@echo 'w' >> ceddep
	@ed - cmakedep < ceddep
	@rm ceddep
	@cat < cmakedep >> makedep
	@rm cmakedep
	@echo '# DO NOT EDIT THIS FILE HERE.' > .Makefile.dep
	@cat < makedep >> .Makefile.dep
	@echo '# DO NOT EDIT THIS FILE HERE.' >> .Makefile.dep
	@rm makedep

.Makefile.dep: 
	@cat < /dev/null > .Makefile.dep

include .Makefile.dep
