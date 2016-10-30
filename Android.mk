LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS  += \
	-Wall -O3 \
	-DLIBVNCSERVER_WITH_WEBSOCKETS \
	-DLIBVNCSERVER_HAVE_LIBPNG \
	-DLIBVNCSERVER_HAVE_ZLIB \
	-DLIBVNCSERVER_HAVE_LIBJPEG

LOCAL_LDLIBS += -lssl -ljpeg -lpng -lutils -llog -lz -ldl

LOCAL_SRC_FILES += \
	droidvncserver.c \
	gui.c \
	inputMethods/input.c \
	screenMethods/framebuffer.c \
	screenMethods/flinger.cpp \
	suinput/suinput.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/screenMethods \
	$(LOCAL_PATH)/inputMethods \
	$(LOCAL_PATH)/suinput \
	bionic/libc/kernel/uapi \
	external/libvncserver \
	external/zlib

LOCAL_SHARED_LIBRARIES := libgui libui libbinder libcutils
LOCAL_SHARED_LIBRARIES += libz libpng libjpeg libssl libcrypto

LOCAL_STATIC_LIBRARIES := libvncserver

LOCAL_MODULE := droidvncserver

LOCAL_CFLAGS += -fPIE
LOCAL_LDFLAGS += -fPIE -pie

include $(BUILD_EXECUTABLE)
