#include <jni.h>
#include <string>

//
using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_coder_hcj_nativeapp_lib_Test_getStringData(
        JNIEnv *env,
        jobject obj /* this */) {
    string hello = "this data is from native";
    return env->NewStringUTF(hello.c_str());
}