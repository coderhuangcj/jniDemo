#include <jni.h>
#include <string>
#include <android/log.h>
#include <algorithm>

#define  LOG_TAG    "nativeprint"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_getNativeData(
        JNIEnv *env,
        jobject obj /* this */) {
    string hello = "this data is from native";
    return env->NewStringUTF(hello.c_str());
}

//java调用native native再调用java的方法
extern "C" JNIEXPORT void JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_accessMethod(
        JNIEnv *env,
        jobject obj /* this */) {
    LOGI("accessMethod");
    jclass jcla = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(jcla, "nativeCall", "()I");
    jint result = env->CallIntMethod(obj, mid);
}

//测试native调用java的static function
extern "C"
JNIEXPORT void JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_accessStaticMethod(JNIEnv *env, jobject obj) {
    jclass js = env->GetObjectClass(obj);
    jmethodID mid = env->GetStaticMethodID(js, "nativeStaticCall", "()V");
    env->CallStaticVoidMethod(js, mid);
}

//java调用native native再访问java的属性
extern "C" JNIEXPORT void JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_accessField(
        JNIEnv *env,
        jobject obj /* this */) {
    LOGI("执行accessField");
    jclass jcla = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(jcla, "number", "I");
    env->SetIntField(obj, fid, 30);
}

//java调用native native再访问java 中object的属性
extern "C" JNIEXPORT void JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_accessFieldString(
        JNIEnv *env,
        jobject obj /* this */) {
    jclass jla = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(jla, "data", "Ljava/lang/String;");
    jstring js = env->NewStringUTF("is modified");
    env->SetObjectField(obj, fid, js);
    env->DeleteLocalRef(js);//删除局部引用
}

//java调用native方法  native方法find java class 并实例化java class 且调用其方法
extern "C" JNIEXPORT void JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_accessClassAndCall(
        JNIEnv *env,
        jobject obj /* this */) {
    jclass jla = env->FindClass("com/coder/hcj/nativeapp/lib/DemoClass");
    jmethodID mid = env->GetMethodID(jla, "<init>", "(Ljava/lang/String;)V");//获取有参构造函数
    jstring jstr = env->NewStringUTF("this data is from native");
    jobject ob = env->NewObject(jla, mid, jstr);
    jmethodID jmid = env->GetMethodID(jla, "callDemo", "()V");
    env->CallVoidMethod(ob, jmid);
    env->DeleteLocalRef(jstr);//删除局部引用
    env->DeleteLocalRef(ob);//删除局部引用

}

//测试jint转int int转jint
extern "C" JNIEXPORT jint JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_count(
        JNIEnv *env,
        jobject obj, jint a, jint b) {
    int na = (int) a;
    int nb = (int) b;
    jint result = (jint) (na + nb);
    return result;
}

//测试string jstring的类型互转
extern "C"
JNIEXPORT jstring JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_stringAndjstring(JNIEnv *env, jobject instance,
                                                            jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);
    string data(str);
    data += ",this is native add string";
    env->ReleaseStringUTFChars(str_, str);
    return env->NewStringUTF(data.c_str());
}

//测试数组排序 冒泡排序
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_coder_hcj_nativeapp_lib_NativeLib_shortAsc(JNIEnv *env, jobject instance,
                                                    jintArray array_) {
    jint *arr = env->GetIntArrayElements(array_, NULL);
    int len = (int) (env->GetArrayLength(array_));
    int array[len];
    for (int i = 0; i < len; i++) {
        array[i] = *arr;
        arr++;
    }

    for (int i = 0; i < len - 1; i++)
        for (int j = 0; j < len - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }

    //0：Java数组进行更新，并且释放C/C++数组
    //JNI_ABORT：Java数组不进行更新，但是释放C/C++数组
    //JNI_COMMIT：Java数组进行更新，不释放C/C++数组(函数执行完后，数组还是会释放的)
    env->ReleaseIntArrayElements(array_, arr, 0);

    jintArray result = env->NewIntArray(len);//创建一个jintArray
    jint jarr[len];
    for (int i = 0; i < len; i++) {//将int[] 转换成  jint[]
        jarr[i] = (jint) array[i];
    }
    env->SetIntArrayRegion(result, 0, len, jarr);//将jint[]转换成jintArray
    return result;
}