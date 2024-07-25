
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceFlushGPUDirectRDMAWrites)(enum cudaFlushGPUDirectRDMAWritesTarget, enum cudaFlushGPUDirectRDMAWritesScope);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceFlushGPUDirectRDMAWrites(enum cudaFlushGPUDirectRDMAWritesTarget target, enum cudaFlushGPUDirectRDMAWritesScope scope) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceFlushGPUDirectRDMAWrites)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceFlushGPUDirectRDMAWrites = (cudaError_t (*)(enum cudaFlushGPUDirectRDMAWritesTarget, enum cudaFlushGPUDirectRDMAWritesScope)) dlsym(libcudart_handle, "cudaDeviceFlushGPUDirectRDMAWrites");
			fprintf(stderr, "cudaDeviceFlushGPUDirectRDMAWrites:%p\n", wrapper_cudaDeviceFlushGPUDirectRDMAWrites);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceFlushGPUDirectRDMAWrites():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceFlushGPUDirectRDMAWrites(target, scope);
		return retval;
	}
}

