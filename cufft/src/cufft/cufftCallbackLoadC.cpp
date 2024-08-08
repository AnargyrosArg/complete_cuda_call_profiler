#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftComplex (*wrapper_cufftCallbackLoadC)(void *, size_t, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftComplex cufftCallbackLoadC(void *dataIn, size_t offset, void *callerInfo, void *sharedPointer){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCallbackLoadC)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCallbackLoadC = (cufftComplex (*)(void *, size_t, void *, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCallbackLoadC");
			fprintf(stderr, "wrapper_cufftCallbackLoadC:%p\n", wrapper_cufftCallbackLoadC);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCallbackLoadC():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftComplex retval = wrapper_cufftCallbackLoadC(dataIn, offset, callerInfo, sharedPointer);
		return retval;
	}
}