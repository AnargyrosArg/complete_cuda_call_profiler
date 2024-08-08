
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaCreateSurfaceObject)(cudaSurfaceObject_t *, const struct cudaResourceDesc *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaCreateSurfaceObject(cudaSurfaceObject_t *pSurfObject, const struct cudaResourceDesc *pResDesc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaCreateSurfaceObject)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaCreateSurfaceObject = (cudaError_t (*)(cudaSurfaceObject_t *, const struct cudaResourceDesc *)) dlsym(libcudart_handle, "cudaCreateSurfaceObject");
			fprintf(stderr, "cudaCreateSurfaceObject:%p\n", wrapper_cudaCreateSurfaceObject);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaCreateSurfaceObject():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaCreateSurfaceObject(pSurfObject, pResDesc);
		return retval;
	}
}

