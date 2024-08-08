
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetSurfaceObjectResourceDesc)(struct cudaResourceDesc *, cudaSurfaceObject_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetSurfaceObjectResourceDesc(struct cudaResourceDesc *pResDesc, cudaSurfaceObject_t surfObject) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetSurfaceObjectResourceDesc)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetSurfaceObjectResourceDesc = (cudaError_t (*)(struct cudaResourceDesc *, cudaSurfaceObject_t)) dlsym(libcudart_handle, "cudaGetSurfaceObjectResourceDesc");
			fprintf(stderr, "cudaGetSurfaceObjectResourceDesc:%p\n", wrapper_cudaGetSurfaceObjectResourceDesc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetSurfaceObjectResourceDesc():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetSurfaceObjectResourceDesc(pResDesc, surfObject);
		return retval;
	}
}

