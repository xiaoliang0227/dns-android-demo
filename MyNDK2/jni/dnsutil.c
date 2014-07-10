#include "com_util_dns_DnsUtil.h"
#include "dns.h"
#include <string.h>

//导入日志头文件
#include <android/log.h>
//修改日志tag中的值
#define LOG_TAG "logfromc"

//日志显示的等级
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

// java中的jstring, 转化为c的一个字符数组
char* Jstring2CStr(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = (*env)->FindClass(env, "java/lang/String");
	jstring strencode = (*env)->NewStringUTF(env, "GB2312");
	jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes",
			"(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
			strencode); // String .getByte("GB2312");
	jsize alen = (*env)->GetArrayLength(env, barr);
	jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*) malloc(alen + 1); //new   char[alen+1]; "\0"
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	(*env)->ReleaseByteArrayElements(env, barr, ba, 0); //释放内存

	return rtn;
}

int size(char *ptr) {
	//variable used to access the subsequent array elements.
	int offset = 0;
	//variable that counts the number of elements in your array
	int count = 0;

	//While loop that tests whether the end of the array has been reached
	while (*(ptr + offset) != '\0') {
		//increment the count variable
		++count;
		//advance to the next element of the array
		++offset;
	}
	//return the size of the array
	return count;
}

JNIEXPORT jstring JNICALL Java_com_util_dns_DnsUtil_getTxtRecord(JNIEnv *env,
		jobject obj, jstring str) {
	char* p = Jstring2CStr(env, str);
	LOGI("getTxtRecord:%s", p);
	my_dns_query(DNS_T_TXT,"all","send-query", p);
	return (*env)->NewStringUTF(env, dns_txt_record);
}

JNIEXPORT jstring JNICALL Java_com_util_dns_DnsUtil_getARecord(JNIEnv *env,
		jobject obj, jstring str, jstring server) {
	char* p = Jstring2CStr(env, str);
	char* s = Jstring2CStr(env, server);
	LOGI("getARecord:%s", p);
	my_dns_query(DNS_T_A,p,"send-query", s);
	return (*env)->NewStringUTF(env, dns_txt_record);
}

JNIEXPORT jstring JNICALL Java_com_util_dns_DnsUtil_getPtrRecord(JNIEnv *env,
		jobject obj, jstring str, jstring server) {
	char* p = Jstring2CStr(env, str);
	char* s = Jstring2CStr(env, server);
	LOGI("getPtrRecord:%s", p);
	my_dns_query(DNS_T_PTR,p,"send-query", s);
	return (*env)->NewStringUTF(env, dns_txt_record);
}
