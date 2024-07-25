#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_cufftCallbackStoreR)(void *, size_t, cufftReal, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	void cufftCallbackStoreR(void *dataOut, size_t offset, cufftReal element, void *callerInfo, void *sharedPointer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCallbackStoreR)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCallbackStoreR = (void (*)(void *, size_t, cufftReal, void *, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCallbackStoreR");
			fprintf(stderr, "wrapper_cufftCallbackStoreR:%p\n", wrapper_cufftCallbackStoreR);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCallbackStoreR():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_cufftCallbackStoreR(dataOut, offset, element, callerInfo, sharedPointer);
	}
}