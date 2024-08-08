
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpy3DAsync)(const struct cudaMemcpy3DParms *, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpy3DAsync(const struct cudaMemcpy3DParms *p, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpy3DAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpy3DAsync = (cudaError_t (*)(const struct cudaMemcpy3DParms *, cudaStream_t)) dlsym(libcudart_handle, "cudaMemcpy3DAsync");
			fprintf(stderr, "cudaMemcpy3DAsync:%p\n", wrapper_cudaMemcpy3DAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpy3DAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpy3DAsync(p, stream);
		return retval;
	}
}

