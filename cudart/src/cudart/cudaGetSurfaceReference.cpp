
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetSurfaceReference)(const struct surfaceReference **, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetSurfaceReference(const struct surfaceReference **surfref, const void *symbol) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetSurfaceReference)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetSurfaceReference = (cudaError_t (*)(const struct surfaceReference **, const void *)) dlsym(libcudart_handle, "cudaGetSurfaceReference");
			fprintf(stderr, "cudaGetSurfaceReference:%p\n", wrapper_cudaGetSurfaceReference);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetSurfaceReference():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetSurfaceReference(surfref, symbol);
		return retval;
	}
}

