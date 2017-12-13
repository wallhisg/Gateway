
LOCAL_DIRS	:= lib
LOCAL_MDLS	:= 
LOCAL_INCS	:= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

LOCAL_SRCS	:= $(foreach sdir, $(LOCAL_DIRS)/$(LOCAL_MDLS), $(wildcard $(sdir)/*.cpp))
LOCAL_OBJS	:= $(patsubst %.cpp, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.cpp, %.deps, $(LOCAL_SRCS))

LOCAL_LIBS	:= $(LOCAL_DIRS)/$(LOCAL_MDLS)/libLib.a

SRCS	+= $(sort $(LOCAL_SRCS))
DEPS	+= $(sort $(LOCAL_DEPS))
TMPS	+= $(sort $(LOCAL_OBJS))
LIBS	+= $(sort $(LOCAL_LIBS))

$(LOCAL_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(LOCAL_LIBS): $(LOCAL_OBJS)
	$(AR) $(ARFLAGS) $@ $<
	
$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	$(CPP) -MM $< > $@
	$(CPP) $< -MM -MT $@ >> $@
