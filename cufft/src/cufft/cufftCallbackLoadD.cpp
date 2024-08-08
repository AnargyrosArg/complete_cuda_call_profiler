#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftDoubleReal (*wrapper_cufftCallbackLoadD)(void *, size_t, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftDoubleReal cufftCallbackLoadD(void *dataIn, size_t offset, void *callerInfo, void *sharedPointer){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCallbackLoadD)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCallbackLoadD = (cufftDoubleReal (*)(void *, size_t, void *, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCallbackLoadD");
			fprintf(stderr, "wrapper_cufftCallbackLoadD:%p\n", wrapper_cufftCallbackLoadD);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCallbackLoadD():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftDoubleReal retval = wrapper_cufftCallbackLoadD(dataIn, offset, callerInfo, sharedPointer);
		return retval;
	}
}