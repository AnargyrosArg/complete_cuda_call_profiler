/*#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_CUpti_BuffersCallbackRequestFunc)(uint8_t **, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	void CUpti_BuffersCallbackRequestFunc(uint8_t **buffer, size_t *size, size_t *maxNumRecords) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_CUpti_BuffersCallbackRequestFunc)
		{
			//fetch the original function addr using dlsym
			wrapper_CUpti_BuffersCallbackRequestFunc = (void (*)(uint8_t **, size_t *, size_t *)) dlsym(libwrapper_cupti_handle, "wrapper_CUpti_BuffersCallbackRequestFunc");
			fprintf(stderr, "wrapper_CUpti_BuffersCallbackRequestFunc:%p\n", wrapper_CUpti_BuffersCallbackRequestFunc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function CUpti_BuffersCallbackRequestFunc():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_CUpti_BuffersCallbackRequestFunc(buffer, size, maxNumRecords);
	}
}
*/
