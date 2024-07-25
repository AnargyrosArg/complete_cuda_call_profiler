#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_cufftCallbackStoreD)(void *, size_t, cufftDoubleReal, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	void cufftCallbackStoreD(void *dataOut, size_t offset, cufftDoubleReal element, void *callerInfo, void *sharedPointer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCallbackStoreD)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCallbackStoreD = (void (*)(void *, size_t, cufftDoubleReal, void *, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCallbackStoreD");
			fprintf(stderr, "wrapper_cufftCallbackStoreD:%p\n", wrapper_cufftCallbackStoreD);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCallbackStoreD():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_cufftCallbackStoreD(dataOut, offset, element, callerInfo, sharedPointer);
	}
}