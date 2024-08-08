/*#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_CUpti_BuffersCallbackCompleteFunc)(CUcontext, uint32_t, uint8_t *, size_t, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	void CUpti_BuffersCallbackCompleteFunc(CUcontext context, uint32_t streamId, uint8_t *buffer, size_t size, size_t validSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_CUpti_BuffersCallbackCompleteFunc)
		{
			//fetch the original function addr using dlsym
			wrapper_CUpti_BuffersCallbackCompleteFunc = (void (*)(CUcontext, uint32_t, uint8_t *, size_t, size_t)) dlsym(libwrapper_cupti_handle, "wrapper_CUpti_BuffersCallbackCompleteFunc");
			fprintf(stderr, "wrapper_CUpti_BuffersCallbackCompleteFunc:%p\n", wrapper_CUpti_BuffersCallbackCompleteFunc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function CUpti_BuffersCallbackCompleteFunc():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_CUpti_BuffersCallbackCompleteFunc(context, streamId, buffer, size, validSize);
	}
}
*/
