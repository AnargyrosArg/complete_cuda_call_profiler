
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemset3DAsync)(struct cudaPitchedPtr, int, struct cudaExtent, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemset3DAsync(struct cudaPitchedPtr pitchedDevPtr, int value, struct cudaExtent extent, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemset3DAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemset3DAsync = (cudaError_t (*)(struct cudaPitchedPtr, int, struct cudaExtent, cudaStream_t)) dlsym(libcudart_handle, "cudaMemset3DAsync");
			fprintf(stderr, "cudaMemset3DAsync:%p\n", wrapper_cudaMemset3DAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemset3DAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemset3DAsync(pitchedDevPtr, value, extent, stream);
		return retval;
	}
}

