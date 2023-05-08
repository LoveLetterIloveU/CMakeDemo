#include <jni.h>
#include <string>
#include "../../depedency_code/cpp/Depedency.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_capplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(Depedency::getPrintLog().c_str());
}