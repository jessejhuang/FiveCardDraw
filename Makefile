###
# $Id: Makefile,v 1.14 2001/08/28 19:22:42 cs342 Exp $
###

#		Fill in your name, email address, and the lab number, leaving the quotes
LAST_NAME	= "Huang"
FIRST_NAME	= "Jesse"
EMAIL_ADDRESS	= "jessehuang@wustl.edu" 
LAB_NUMBER	= "3"

#		The name of the executable file
EXECUTABLE	= lab3 

#		Source files you want to compile
#		(NOTE: Don't include header (.h) files, or source (.cc) files
#		that only contain template class method definitions.)
CMPL_SRCS	= Exceptions.cpp Game.cpp card.cpp deck.cpp fiveCardDraw.cpp hand.cpp player.cpp poker.cpp lab3.cpp

#               Source files containing only template class method definitions
TMPL_SRCS	= 

#               Header files
HEADER_FILES    =  Exceptions.h Game.h card.h deck.h fiveCardDraw.h hand.h player.h poker.h

#               Other files to turn in (i.e., readme, output files, etc)
OTHER_FILES     = readme

#               Any special flags that should be set for compilation
SPECIAL_FLAGS  = -pedantic
                                                                             #
#################### DO NOT CHANGE ANYTHING BELOW THIS LINE ###################

#		C++ compiler
CXX		= g++

#		Submissions are normally sent to the grader account
GRADERS		= cse332@cec.wustl.edu
MAILTO		= $(GRADERS)
MAILBACK	= $(EMAIL_ADDRESS)

#               All your source files (needed for executable dependency)
USER_SRCS        = $(CMPL_SRCS) $(TMPL_SRCS) $(HEADER_FILES)

#               Provided source files (i.e., History files, etc)
PROVIDED_SRCS   =

#               All your source files (needed for executable dependency)
ALL_SRCS        = $(USER_SRCS) $(PROVIDED_SRCS)

#               All files to turn in (including readme, output files, etc)
ALL_FILES       = $(USER_SRCS) $(OTHER_FILES)

#               The list of libraries that should be linked in
#LIBS    =       -lsocket -lnsl
LIBS    =       -lnsl

#               The name of the compiler
CCC      = $(CXX)

#               The name of the previewer (pageview or ghostview)
PREVIEWER = /usr/openwin/bin/pageview -right

#              Names of object files (from names of source files)
OBJS     = $(CMPL_SRCS:.cc=.o)

#               Any define flags that should be set for conditional compilation
DEFFLAGS  = -DUNIX

#               Any general flags that should be set for the compiler
#               NOTE: to optimize fully, change -g to -O4
CXXFLAGS  =     -Wall -W -g $(SPECIAL_FLAGS)

#               Any -I directories in which there are .h files that should be included
INCFLAGS  =
#               Flags that are specific to SUN object code
SUNFLAGS  =  #-misalign

#               The concatenation of all the flags that the compiler should get
CCFLAGS = $(DEFFLAGS) $(INCFLAGS) $(SUNFLAGS) $(CXXFLAGS)

###
# Targets
###

#               Special "all" target expected by Eclipse.
all: $(EXECUTABLE)

#               Construct the executable
$(EXECUTABLE): Templates.DB $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(CCFLAGS) $(OBJS) $(LIBS)

#		Remove all junk that might be lying around
clean:
	-rm -f *.o core *.bak *~ ../toturnin ./toturnin
	-rm -fr Templates.DB SunWS_cache *.rpo TEST_TURNIN

realclean: clean
	-rm -f $(EXECUTABLE)

toturnin:	clean $(ALL_FILES)
	zip -r - $(ALL_FILES) Makefile \
	  | uuencode "homework.zip" > ../toturnin

turnin: toturnin
	@if [ $(LAST_NAME) = 'YOUR LAST NAME GOES HERE' -o \
	      $(FIRST_NAME) = 'YOUR FIRST NAME GOES HERE' -o \
	      $(EMAIL_ADDRESS) = "YOUR EMAIL ADDRESS GOES HERE" -o \
	      $(LAB_NUMBER) = 'THE LAB NUMBER GOES HERE' ]; \
          then echo 'ERROR: you must edit your Makefile to set LAST_NAME/FIRST_NAME/EMAIL_ADDRESS/LAB_NUMBER!'; \
	else \
	  cat ../toturnin \
	    | Mail -s "Assignment $(LAB_NUMBER) $(LAST_NAME)_$(FIRST_NAME)" $(MAILTO); \
	fi

return: toturnin
	  cat ../toturnin \
	    | Mail -s "Graded Assignment $(LAB_NUMBER) $(LAST_NAME)_$(FIRST_NAME)" $(MAILBACK);

test_turnin: toturnin
	@if [ $(LAST_NAME) = 'YOUR LAST NAME GOES HERE' -o \
	      $(FIRST_NAME) = 'YOUR FIRST NAME GOES HERE' -o \
	      $(EMAIL_ADDRESS) = "YOUR EMAIL ADDRESS GOES HERE" -o \
	      $(LAB_NUMBER) = 'THE LAB NUMBER GOES HERE' ]; \
          then echo 'ERROR: you must edit your Makefile to set LAST_NAME/FIRST_NAME/EMAIL_ADDRESS/LAB_NUMBER!'; \
	else \
	  (test -d TEST_TURNIN || mkdir TEST_TURNIN; cd TEST_TURNIN; \
           uudecode ../../toturnin; unzip homework.zip; /bin/rm homework.zip); \
	  echo ' '; \
	  echo 'You just _tested_ turnin, you did _not_ turn anything in!!!!'; \
	  echo 'Please make sure that the contents of the TEST_TURNIN'; \
	  echo 'directory are exactly what you want to turn in!'; \
	  echo 'Then, use "make turnin" to actually turn in your assignment.'; \
	fi

#		Preview the .h and .c files
preview:
	$(ENSCRIPT) -2Gr \
        -b$(LAST_NAME)", "$(FIRST_NAME)" : $(LOGNAME)@cec.wustl.edu" \
        -p - $(ALL_FILES) | $(PREVIEWER) -

#		Change the Makefile to reflect the correct dependencies.
depend:
	-rm -f ccdep
	-rm -f eddep
	$(CXX) -xM $(CCFLAGS) $(CMPL_SRCS) > ccdep
	sed -n '1,/^# DO NOT DELETE THIS LINE/p' Makefile > eddep
	echo \#\#\# >> eddep
	cat ccdep >> eddep
	cp Makefile Makefile.bak
	mv eddep Makefile
	rm ccdep

.SUFFIXES: .cpp
.cpp.o:
	$(COMPILE.cc) $(CCFLAGS) $(OUTPUT_OPTION) $<
.cpp:
	$(LINK.cc) $(LDFLAGS) -o $@ $< $(LDLIBS)

main.o: $(ALL_SRCS) Makefile

#### To avoid Sun CC warning about having to create Templates.DB.
Templates.DB:
	@test -d $@ || mkdir $@

###
# OBJECT FILE DEPENDENCIES FOLLOW.
#
# DO NOT DELETE THIS LINE -- make depend uses it
###
