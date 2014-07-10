LOCAL_PATH := $(call my-dir)

# The final shared library that will be bundled inside the .apk
include ${CLEAR_VARS}
LOCAL_MODULE := dnsutil
LOCAL_LDLIBS := -landroid -llog
LOCAL_CFLAGS := -std=gnu99 -DDNS_MAIN -Wall -Wno-unused-function -Wno-unused-parameter -O2 -g -fstack-protector
LOCAL_SRC_FILES := dnsutil.c dns.c
include ${BUILD_SHARED_LIBRARY}
