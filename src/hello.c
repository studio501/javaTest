#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "../include/myjni_HelloWorld.h"
#include "../helloImpl.h"

JNIEXPORT void JNICALL Java_myjni_HelloWorld_sayHello(JNIEnv *env, jobject thisObj)
  {
  	//printf("this hello from hello.c ok? fuck windows power shell and funk mingw64!!!!!!!!!!!\n");
  	sayHello();
  	return ;
  }

JNIEXPORT jdouble JNICALL Java_myjni_HelloWorld_average(JNIEnv *env, jobject thisObj, jint v1, jint v2)
{
	//return (v1 + v2) / 2;
	return calculateAvg(v1,v2);
}

JNIEXPORT void JNICALL Java_myjni_HelloWorld_others
  (JNIEnv *env, jobject thisObj)
{
	others();
	return;
}