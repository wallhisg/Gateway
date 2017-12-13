TARGET		:= IoServer

LOCAL_DIRS	:= app
LOCAL_MDLS	:= 
LOCAL_INCS	:= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

PROGRAM		:= $(LOCAL_DIRS)/$(LOCAL_MDLS)/$(TARGET)

LOCAL_SRCS	:= $(foreach sdir, $(LOCAL_DIRS)/$(LOCAL_MDLS), $(wildcard $(sdir)/*.cpp))
LOCAL_OBJS	:= $(patsubst %.cpp, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.cpp, %.deps, $(LOCAL_SRCS))

SRCS		+= $(sort $(LOCAL_SRCS))
DEPS		+= $(sort $(LOCAL_DEPS))
TMPS		+= $(sort $(LOCAL_OBJS))
PROGRAMS	+= $(PROGRAM)

LOCAL_WT_LIBS	= -lwthttp -lwt -lboost_system -lboost_serialization -lpthread

$(PROGRAM): $(LOCAL_OBJS) $(OBJS) $(LIBS)
	$(CPP) $(LOCAL_OBJS) $(OBJS) $(LIBS) $(LOCAL_WT_LIBS) -o $@
	
$(LOCAL_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CPP) -MM $< > $@
	@$(CPP) $< -MM -MT $@ >> $@




