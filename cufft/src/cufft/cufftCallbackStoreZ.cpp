#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_cufftCallbackStoreZ)(void *, size_t, cufftDoubleComplex, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	void cufftCallbackStoreZ(void *dataOut, size_t offset, cufftDoubleComplex element, void *callerInfo, void *sharedPointer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCallbackStoreZ)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCallbackStoreZ = (void (*)(void *, size_t, cufftDoubleComplex, void *, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCallbackStoreZ");
			fprintf(stderr, "wrapper_cufftCallbackStoreZ:%p\n", wrapper_cufftCallbackStoreZ);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCallbackStoreZ():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_cufftCallbackStoreZ(dataOut, offset, element, callerInfo, sharedPointer);
	}
}