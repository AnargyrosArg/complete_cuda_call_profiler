
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetAttribute)(int *, enum cudaDeviceAttr, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetAttribute(int *value, enum cudaDeviceAttr attr, int device) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetAttribute = (cudaError_t (*)(int *, enum cudaDeviceAttr, int)) dlsym(libcudart_handle, "cudaDeviceGetAttribute");
			fprintf(stderr, "cudaDeviceGetAttribute:%p\n", wrapper_cudaDeviceGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetAttribute(value, attr, device);
		return retval;
	}
}

