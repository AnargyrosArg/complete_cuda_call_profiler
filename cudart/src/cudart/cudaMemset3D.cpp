
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemset3D)(struct cudaPitchedPtr, int, struct cudaExtent);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemset3D(struct cudaPitchedPtr pitchedDevPtr, int value, struct cudaExtent extent) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemset3D)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemset3D = (cudaError_t (*)(struct cudaPitchedPtr, int, struct cudaExtent)) dlsym(libcudart_handle, "cudaMemset3D");
			fprintf(stderr, "cudaMemset3D:%p\n", wrapper_cudaMemset3D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemset3D():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemset3D(pitchedDevPtr, value, extent);
		return retval;
	}
}

