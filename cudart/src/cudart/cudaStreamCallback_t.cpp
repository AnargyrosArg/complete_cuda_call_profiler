
/*#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_cudaStreamCallback_t)(cudaStream_t, cudaError_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	void cudaStreamCallback_t(cudaStream_t stream, cudaError_t status, void *userData) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamCallback_t)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamCallback_t = (void (*)(cudaStream_t, cudaError_t, void *)) dlsym(libcudart_handle, "cudaStreamCallback_t");
			fprintf(stderr, "cudaStreamCallback_t:%p\n", wrapper_cudaStreamCallback_t);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamCallback_t():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_cudaStreamCallback_t(stream, status, userData);
	}
}
*/


