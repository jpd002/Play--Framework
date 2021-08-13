#include "android/android_net_Uri.h"

#include <cassert>
#include "android/JavaVM.h"

using namespace android::net;

void Uri_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("android/net/Uri");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	parse = env->GetStaticMethodID(clazz, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
	Framework::CJavaVM::CheckException(env);
	assert(parse != NULL);
}

Uri Uri::parse(jstring uriString)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jobject uriObject = env->CallStaticObjectMethod(classInfo.clazz, classInfo.parse, uriString);
	Framework::CJavaVM::CheckException(env);

	Uri uri;
	uri.Attach(uriObject);
	return uri;
}
