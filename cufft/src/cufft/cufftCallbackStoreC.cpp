#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_cufftCallbackStoreC)(void *, size_t, cufftComplex, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	void cufftCallbackStoreC(void *dataOut, size_t offset, cufftComplex element, void *callerInfo, void *sharedPointer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCallbackStoreC)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCallbackStoreC = (void (*)(void *, size_t, cufftComplex, void *, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCallbackStoreC");
			fprintf(stderr, "wrapper_cufftCallbackStoreC:%p\n", wrapper_cufftCallbackStoreC);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCallbackStoreC():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_cufftCallbackStoreC(dataOut, offset, element, callerInfo, sharedPointer);
	}
}