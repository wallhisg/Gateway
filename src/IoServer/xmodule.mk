
LOCAL_DIRS	:= src
LOCAL_MDLS	:= IoServer
LOCAL_INCS	:= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

LOCAL_SRCS	:= $(foreach sdir, $(LOCAL_DIRS)/$(LOCAL_MDLS), $(wildcard $(sdir)/*.cpp))
LOCAL_OBJS	:= $(patsubst %.cpp, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.cpp, %.deps, $(LOCAL_SRCS))

SRCS	+= $(sort $(LOCAL_SRCS))
OBJS	+= $(sort $(LOCAL_OBJS))
DEPS	+= $(sort $(LOCAL_DEPS))

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CPP) -MM $< > $@
	@$(CPP) $< -MM -MT $@ >> $@

$(LOCAL_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)
