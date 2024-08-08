#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftReal (*wrapper_cufftCallbackLoadR)(void *, size_t, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftReal cufftCallbackLoadR(void *dataIn, size_t offset, void *callerInfo, void *sharedPointer){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCallbackLoadR)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCallbackLoadR = (cufftReal (*)(void *, size_t, void *, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCallbackLoadR");
			fprintf(stderr, "wrapper_cufftCallbackLoadR:%p\n", wrapper_cufftCallbackLoadR);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCallbackLoadR():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftReal retval = wrapper_cufftCallbackLoadR(dataIn, offset, callerInfo, sharedPointer);
		return retval;
	}
}