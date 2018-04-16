
#ifndef _HELLOIMPL_H__
#define _HELLOIMPL_H__

#include "./include/myjni_HelloWorld.h"

#ifdef __cplusplus
extern "C"{
#endif

	void sayHello();
	jdouble calculateAvg(jint v1,jint v2);
	void others();
#ifdef __cplusplus
};
#endif

#endif