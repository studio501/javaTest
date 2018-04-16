#include "helloImpl.h"
#include <iostream>
#include <string>

using namespace std;

void sayHello()
{
	std::cout<<"hello from c++"<<std::endl;
}

jdouble calculateAvg(jint v1,jint v2)
{
	return (v1 + v2) /2;
}

void others()
{
	std::cout<<"others from c++"<<std::endl;
}

JNIEXPORT jstring JNICALL Java_myjni_HelloWorld_passStrfromJava
  (JNIEnv *env, jobject thisObj, jstring str)
{
	const char * str2 = env->GetStringUTFChars(str,NULL);
	if(NULL == str2) return NULL;

	env->ReleaseStringUTFChars(str,str2);

	string outCStr;
	cout<<"enter a string : "<<endl;
	getline(cin,outCStr);

	outCStr+=(str2);
	//strcat(outCStr,"\n");

	return env->NewStringUTF(outCStr.c_str());
}

JNIEXPORT jdoubleArray JNICALL Java_myjni_HelloWorld_sumAndAverage
  (JNIEnv *env, jobject thisObj, jdoubleArray numArr)
{
	jdouble * inCArray = env->GetDoubleArrayElements(numArr,NULL);
	if(NULL == inCArray) return NULL;
	jsize length = env->GetArrayLength(numArr);

	jdouble sum=0.0;
	for(int i=0;i<length;++i){
		sum+=inCArray[i];
	}
	jdouble avg = (jdouble)sum/length;
	env->ReleaseDoubleArrayElements(numArr,inCArray,0);

	jdouble outCArray[] = {sum,avg};

	jdoubleArray outJniArray = env->NewDoubleArray(2);
	if(NULL == outJniArray) return NULL;
	env->SetDoubleArrayRegion(outJniArray,0,2,outCArray);

	return outJniArray;
}

JNIEXPORT void JNICALL Java_myjni_HelloWorld_modifyInstanceMember(JNIEnv *env, jobject thisObj)
{
	//int
	jclass thisClass = env->GetObjectClass(thisObj);

	jfieldID fidNumber = env->GetFieldID(thisClass,"_number","I");

	if(NULL == fidNumber) return;

	jint number = env->GetIntField(thisObj,fidNumber);
	cout<<"in c++ _number is "<<number<<endl;

	number = 99;
	env->SetIntField(thisObj,fidNumber,number);

	//string
	jfieldID fidMsg = env->GetFieldID(thisClass,"_msg","Ljava/lang/String;");
	if(NULL == fidMsg) return;

	jstring msg = (jstring)env->GetObjectField(thisObj,fidMsg);

	const char * cStr = env->GetStringUTFChars(msg,NULL);

	if(NULL == cStr) return;

	cout<<"inc c++ thi string is "<<cStr<<endl;

	msg = env->NewStringUTF("A new msg form c++");
	if(NULL == msg) return;

	env->SetObjectField(thisObj,fidMsg,msg);

	//array
	jfieldID fidArr = env->GetFieldID(thisClass,"_intArr","[I");
	if(NULL == fidArr) return;

	jintArray temparr = (jintArray)env->GetObjectField(thisObj,fidArr);
	if(NULL == temparr) return;


	jint * intCArray = env->GetIntArrayElements(temparr,NULL);
	if(NULL == intCArray) return;
	jsize length = env->GetArrayLength(temparr);
	for(int i=0;i<length;++i){
		cout<<intCArray[i]<<" ";
	}

	intCArray[0] = 100;

	env->SetObjectField(thisObj,fidArr,temparr);

	env->ReleaseIntArrayElements(temparr,intCArray,0);

	//static member
	jfieldID f_s_idnumber = env->GetStaticFieldID(thisClass,"_s_number","D");
	if(NULL == f_s_idnumber) return;

	jdouble s_number = env->GetStaticDoubleField(thisClass,f_s_idnumber);
	cout<<"in c++ the static double is "<<s_number<<endl;
	s_number = 99.99;
	env->SetStaticDoubleField(thisClass,f_s_idnumber,s_number);

}


JNIEXPORT void JNICALL Java_myjni_HelloWorld_nativeMethod(JNIEnv *env, jobject thisObj)
{
	jclass thisClass = env->GetObjectClass(thisObj);

	jmethodID midCallBack = env->GetMethodID(thisClass,"callback","()V");
	if(NULL == midCallBack) return;

	env->CallVoidMethod(thisObj,midCallBack);

	jmethodID midCallBackStr = env->GetMethodID(thisClass,"callback","(Ljava/lang/String;)V");
	if(midCallBackStr == NULL) return;

	jstring msg = env->NewStringUTF("\ncall str push by c++");
	env->CallVoidMethod(thisObj,midCallBackStr,msg);

	jmethodID midCallbackAvg = env->GetMethodID(thisClass,"callbackAverage","(II)D");
	if(NULL == midCallbackAvg) return;

	jdouble avg = env->CallDoubleMethod(thisObj,midCallbackAvg,2,3);
	cout<<"in c++ avg is "<<avg<<endl;

	jmethodID midCallBackStatic = env->GetStaticMethodID(thisClass,"callbackStatic","()Ljava/lang/String;");
	if(NULL == midCallBackStatic) return;

	jstring resultJNIStr = (jstring)env->CallStaticObjectMethod(thisClass,midCallBackStatic);
	const char * resultStr = env->GetStringUTFChars(resultJNIStr,NULL);
	if(NULL == resultStr) return;
	cout<<"in c++ the returned string is "<<resultStr<<endl;
	env->ReleaseStringUTFChars(resultJNIStr,resultStr);
}