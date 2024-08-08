
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpy3D)(const struct cudaMemcpy3DParms *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpy3D(const struct cudaMemcpy3DParms *p) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpy3D)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpy3D = (cudaError_t (*)(const struct cudaMemcpy3DParms *)) dlsym(libcudart_handle, "cudaMemcpy3D");
			fprintf(stderr, "cudaMemcpy3D:%p\n", wrapper_cudaMemcpy3D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpy3D():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpy3D(p);
		return retval;
	}
}

