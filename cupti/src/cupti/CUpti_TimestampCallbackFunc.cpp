// #include <cupti.h>
// #include <dlfcn.h>
// #include <iostream>
// uint64_t (*wrapper_CUpti_TimestampCallbackFunc)();
// //handle to the libwrapper library, used to fetch original functions with dlsym
// extern void* libwrapper_cupti_handle;
// extern "C"
// {
// 	uint64_t CUpti_TimestampCallbackFunc() {
// 		char* __dlerror;
// 		//this call clears any previous errors
// 		dlerror();
// 		if(libwrapper_cupti_handle == NULL){
// 			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
// 		}
// 		if (!wrapper_CUpti_TimestampCallbackFunc)
// 		{
// 			//fetch the original function addr using dlsym
// 			wrapper_CUpti_TimestampCallbackFunc = (uint64_t (*)()) dlsym(libwrapper_cupti_handle, "wrapper_CUpti_TimestampCallbackFunc");
// 			fprintf(stderr, "wrapper_CUpti_TimestampCallbackFunc:%p\n", wrapper_CUpti_TimestampCallbackFunc);
// 		}
// 		__dlerror = dlerror();
// 		if(__dlerror){
// 			fprintf(stderr, "dlsym error for function CUpti_TimestampCallbackFunc():%s\n", __dlerror);
// 			fflush(stderr);
// 		}
// 		uint64_t retval = wrapper_CUpti_TimestampCallbackFunc();
// 		return retval;
// 	}
// }