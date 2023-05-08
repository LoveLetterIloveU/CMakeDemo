#include <jni.h>
#include <string>
//#include "../../depedency_code/cpp/Depedency.h"
#include <Depedency.h>
#include <c_version.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_capplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "String from C++ : ";
    hello.append(Depedency::getPrintLog());
    hello.append(" | ");
    hello.append(PLAYER_VERSION);
    return env->NewStringUTF(hello.c_str());
}