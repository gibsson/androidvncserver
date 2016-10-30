LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_LDLIBS += -ljpeg -lz -lssl -lpng

LOCAL_SRC_FILES += \
	fbvncserver.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH) \
	external/jpeg \
	external/libvncserver \
	external/zlib

LOCAL_SHARED_LIBRARIES := libz libjpeg libpng libssl libcrypto

LOCAL_STATIC_LIBRARIES := libvncserver

LOCAL_MODULE := androidvncserver

include $(BUILD_EXECUTABLE)
