
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaLaunchKernel)(const void *, dim3, dim3, void **, size_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaLaunchKernel(const void *func, dim3 gridDim, dim3 blockDim, void **args, size_t sharedMem, cudaStream_t stream) {
		fprintf(stderr,"%s()\n",__func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaLaunchKernel)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaLaunchKernel = (cudaError_t (*)(const void *, dim3, dim3, void **, size_t, cudaStream_t)) dlsym(libcudart_handle, "cudaLaunchKernel");
			fprintf(stderr, "cudaLaunchKernel:%p\n", wrapper_cudaLaunchKernel);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaLaunchKernel():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaLaunchKernel(func, gridDim, blockDim, args, sharedMem, stream);
		return retval;
	}
}

