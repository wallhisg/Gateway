
PROGRAMS	:=
SRCS		:=
OBJS		:=
DEPS		:=
LIBS		:= 
TMPS		:= 

BASE_DIR	= .

MODULES		:= src src/Homepage src/IoServer
#Add Modules lib later - lib lib/Ui
MODULES		+= 
MODULES		+= app/IoServer

# NO USER CONFIGURABLE OPTIONS BELOW HERE

#======================================================================
# select which tools to use as compiler, 
# librarian and linker
#======================================================================
CPP = g++
CPPFLAGS = 

INCLUDE_DIRS	:= include
CPPFLAGS += $(addprefix -I , $(INCLUDE_DIRS))
vpath %.h $(INCLUDE_DIRS)
#======================================================================
# select which tools to use as compiler, librarian and linker
AR = ar
ARFLAGS = rv

MKDIR		:= mkdir -p
RM		:= rm -f
MV		:= mf -f

#======================================================================
# Common modules
include $(patsubst %, $(BASE_DIR)/%/xmodule.mk, $(MODULES))
#======================================================================
default: build
#======================================================================
build: killprocess $(OBJS) $(LIBS)
#======================================================================
# Add $(LIBS) later
all: killprocess $(PROGRAMS) $(OBJS) 
#======================================================================
clean:
	$(RM) $(OBJS) $(PROGRAMS) $(LIBS) $(TMPS) $(DEPS)
#======================================================================
run: $(PROGRAMS)
	@$(PROGRAMS) --docroot . --http-address 0.0.0.0 --http-port 8080
	
killprocess:
	@sh kill.sh $(TARGET)

