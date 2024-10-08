
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemAdvise)(const void *, size_t, enum cudaMemoryAdvise, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemAdvise(const void *devPtr, size_t count, enum cudaMemoryAdvise advice, int device) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemAdvise)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemAdvise = (cudaError_t (*)(const void *, size_t, enum cudaMemoryAdvise, int)) dlsym(libcudart_handle, "cudaMemAdvise");
			fprintf(stderr, "cudaMemAdvise:%p\n", wrapper_cudaMemAdvise);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemAdvise():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemAdvise(devPtr, count, advice, device);
		return retval;
	}
}

