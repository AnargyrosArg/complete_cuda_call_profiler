
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetNvSciSyncAttributes)(void *, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetNvSciSyncAttributes(void *nvSciSyncAttrList, int device, int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetNvSciSyncAttributes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetNvSciSyncAttributes = (cudaError_t (*)(void *, int, int)) dlsym(libcudart_handle, "cudaDeviceGetNvSciSyncAttributes");
			fprintf(stderr, "cudaDeviceGetNvSciSyncAttributes:%p\n", wrapper_cudaDeviceGetNvSciSyncAttributes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetNvSciSyncAttributes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetNvSciSyncAttributes(nvSciSyncAttrList, device, flags);
		return retval;
	}
}

