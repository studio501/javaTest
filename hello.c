
#include <jni.h>
#include <stdio.h>
#include "HelloWorld.h"
#include "helloImpl.h"

JNIEXPORT void JNICALL Java_HelloWorld_sayHello(JNIEnv *env, jobject thisObj)
  {
  	//printf("this hello from hello.c ok? fuck windows power shell and funk mingw64!!!!!!!!!!!\n");
  	sayHello();
  	return ;
  }