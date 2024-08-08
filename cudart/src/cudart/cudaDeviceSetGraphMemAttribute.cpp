
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceSetGraphMemAttribute)(int, enum cudaGraphMemAttributeType, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceSetGraphMemAttribute(int device, enum cudaGraphMemAttributeType attr, void *value) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceSetGraphMemAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceSetGraphMemAttribute = (cudaError_t (*)(int, enum cudaGraphMemAttributeType, void *)) dlsym(libcudart_handle, "cudaDeviceSetGraphMemAttribute");
			fprintf(stderr, "cudaDeviceSetGraphMemAttribute:%p\n", wrapper_cudaDeviceSetGraphMemAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceSetGraphMemAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceSetGraphMemAttribute(device, attr, value);
		return retval;
	}
}

