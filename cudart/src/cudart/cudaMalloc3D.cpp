
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMalloc3D)(struct cudaPitchedPtr *, struct cudaExtent);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMalloc3D(struct cudaPitchedPtr *pitchedDevPtr, struct cudaExtent extent) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMalloc3D)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMalloc3D = (cudaError_t (*)(struct cudaPitchedPtr *, struct cudaExtent)) dlsym(libcudart_handle, "cudaMalloc3D");
			fprintf(stderr, "cudaMalloc3D:%p\n", wrapper_cudaMalloc3D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMalloc3D():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMalloc3D(pitchedDevPtr, extent);
		return retval;
	}
}

