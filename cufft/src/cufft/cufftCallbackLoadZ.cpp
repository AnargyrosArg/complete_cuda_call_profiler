#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftDoubleComplex (*wrapper_cufftCallbackLoadZ)(void *, size_t, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftDoubleComplex cufftCallbackLoadZ(void *dataIn, size_t offset, void *callerInfo, void *sharedPointer){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCallbackLoadZ)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCallbackLoadZ = (cufftDoubleComplex (*)(void *, size_t, void *, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCallbackLoadZ");
			fprintf(stderr, "wrapper_cufftCallbackLoadZ:%p\n", wrapper_cufftCallbackLoadZ);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCallbackLoadZ():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftDoubleComplex retval = wrapper_cufftCallbackLoadZ(dataIn, offset, callerInfo, sharedPointer);
		return retval;
	}
}