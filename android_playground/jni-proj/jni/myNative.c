#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>
#define ARRAY_LENGTH 5

#if 0
JNIEXPORT jobjectArray JNICALL Java_com_dizuo_xapp_MainActivity_getStringArray(JNIEnv *env, jobject obj , jstring string)
#endif 

jobjectArray Java_com_dizuo_xapp_MainActivity_getStringArray(JNIEnv *env, jobject obj , jstring string)

{
    jclass objClass = (*env)->FindClass(env , "java/lang/String");
    jobjectArray texts = (*env)->NewObjectArray(env ,
                                 (jsize)ARRAY_LENGTH , objClass , 0);
    jstring jstr;
    char* sa[] = {"HelloNDK!!" , "Geolo" , "JNI" , "你好" , "我不好"};
    int i = 0;
    for(; i<ARRAY_LENGTH ; i++){
       jstr = (*env)->NewStringUTF(env , sa[i]);
       (*env)->SetObjectArrayElement(env, texts, i, jstr);//必须放入jstring
    }
    return texts;
}
