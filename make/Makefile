#/***********************************************************************
#* SVN: Version Control with Subversion
#* ---------------------------------------------------------------------
#* $Id$
#***********************************************************************
#* LICENSE AND WARRANTY INFORMATION
#* ================================
#* Version V1.0/1417-2011-04-27-162001
#* Copyright (C) 2011
#* Forschungseinrichtung Satellitengeodaesie, TU Muenchen &
#* Bundesamt fuer Kartographie und Geodaesie
#* Geodetic Observatory Wettzell
#* Sackenrieder Str. 25
#* D-93444 Bad Koetzting
#* Germany
#*
#* This program is FREE SOFTWARE under the terms of GNU Lesser General
#* Public License v3 (or any later version) and may be used following
#* this definitions as published by the Free Software Foundation at
#* http://www.gnu.de/documents/lgpl-3.0.en.html. Software parts which
#* include elements from external software distributions may be under
#* different licenses as the Sun License/BSD License for the ONC/Sun RPC
#* (http://www.opensource.org/licenses/bsd-license.php)
#* and the wxWindows Library Licence for the GUI parts with wxWidgets
#* (http://www.opensource.org/licenses/wxwindows.php).
#* In case of variations to the above licenses each particular developer
#* is responsible for defining the dedicated license conditions and terms.
#*
#* This program is distributed in the hope that it will be useful.
#* IT IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING
#* THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A
#* PARTICULAR PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE
#* OR TRADE PRACTICE.
#*
#* The software is provided with no support and without any obligation
#* on the part of the Geodetic Observatory Wettzell to assist in its
#* use, correction, modification or enhancement. THE Geodetic Observatory
#* Wettzell SHALL HAVE NO LIABILITY WITH RESPECT TO THE INFRINGEMENT OF
#* COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY THE SOFTWARE OR ANY PART
#* THEREOF. In no event will the Geodetic Observatory Wettzell be liable
#* for any lost revenue or profits or other special, indirect and
#* consequential damages, even if the Geodetic Observatory Wettzell
#* has been advised of the possibility of such damages.
#*
#* You should have received a copy of the license(s) along with this program.
#**********************************************************************/
 
#***********************************************************************
#* Description:                                                        *
#* ------------                                                        *
#*                                                                     *
#* Author: Martin Ettl (ettl@fs.wettzell.de)                           *
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

BIN_DIR 	= ../bin
OBJ_DIR 	= ../obj
SRC_DIR 	= ../src
SRC_EXT_DIR 	= ../srcext
RPC_DIR 	= ../rpc


CPPCOMPILER 		= g++
CPP_INCLUDE_HEADER 	= 
CPPCOMPILER_FLAGS 	= -O2 -W -Wall -Wunused -Wextra -ansi -pedantic -Wno-write-strings -fno-strict-aliasing
CPPCOMPILER_CALL 	= $(CPPCOMPILER) -c $(CPP_INCLUDE_HEADER) $(CPPCOMPILER_FLAGS) -o $@ $< 

CCOMPILER 		= gcc
CCOMPILER_FLAGS 	= -O2 -W -Wall -Wunused -Wextra -ansi -pedantic   
CCOMPILER_CALL  	= $(CCOMPILER) -c $(CCOMPILER_FLAGS) -o $@ $< 

LINKER = $(CPPCOMPILER) 
LINKER_FLAGS = 
LINKER_CALL = $(LINKER) -o $@ $^ $(LINKER_FLAGS)


all: $(BIN_DIR)/test

# ============================================================
# LINKER-RULES
# ===========================================================
$(BIN_DIR)/test : $(OBJ_DIR)/application.o
	$(LINKER_CALL)
# 
# ===========================================================
# c++ - SOURCES
# ===========================================================
SRCS = $(SRC_DIR)/application.cpp


# ===========================================================
# c - SOURCES
# =========================================================== 
CSRCS = 

# ===========================================================
# SUPPORTING-RULES
# ===========================================================
build: mrproper depend 
	# after generating the dependencies it is necessary to call make again
	make all 

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
		 (echo $$i; $(CPPCOMPILER) $(CPPCOMPILER_FLAGS) -MM $$i >> makedep); done
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
		 (echo $$i; $(CCOMPILER) $(CCOMPILER_FLAGS) -MM $$i >> cmakedep); done
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
