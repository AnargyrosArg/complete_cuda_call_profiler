
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemcpy3DPeer)(const struct cudaMemcpy3DPeerParms *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemcpy3DPeer(const struct cudaMemcpy3DPeerParms *p) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemcpy3DPeer)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemcpy3DPeer = (cudaError_t (*)(const struct cudaMemcpy3DPeerParms *)) dlsym(libcudart_handle, "cudaMemcpy3DPeer");
			fprintf(stderr, "cudaMemcpy3DPeer:%p\n", wrapper_cudaMemcpy3DPeer);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemcpy3DPeer():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemcpy3DPeer(p);
		return retval;
	}
}

