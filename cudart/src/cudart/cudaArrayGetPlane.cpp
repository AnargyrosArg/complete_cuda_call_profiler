
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaArrayGetPlane)(cudaArray_t *, cudaArray_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaArrayGetPlane(cudaArray_t *pPlaneArray, cudaArray_t hArray, unsigned int planeIdx) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaArrayGetPlane)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaArrayGetPlane = (cudaError_t (*)(cudaArray_t *, cudaArray_t, unsigned int)) dlsym(libcudart_handle, "cudaArrayGetPlane");
			fprintf(stderr, "cudaArrayGetPlane:%p\n", wrapper_cudaArrayGetPlane);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaArrayGetPlane():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaArrayGetPlane(pPlaneArray, hArray, planeIdx);
		return retval;
	}
}

