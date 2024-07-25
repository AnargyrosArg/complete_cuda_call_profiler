
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDestroySurfaceObject)(cudaSurfaceObject_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDestroySurfaceObject(cudaSurfaceObject_t surfObject) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDestroySurfaceObject)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDestroySurfaceObject = (cudaError_t (*)(cudaSurfaceObject_t)) dlsym(libcudart_handle, "cudaDestroySurfaceObject");
			fprintf(stderr, "cudaDestroySurfaceObject:%p\n", wrapper_cudaDestroySurfaceObject);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDestroySurfaceObject():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDestroySurfaceObject(surfObject);
		return retval;
	}
}

