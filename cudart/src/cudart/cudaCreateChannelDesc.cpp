
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
struct cudaChannelFormatDesc (*wrapper_cudaCreateChannelDesc)(int, int, int, int, enum cudaChannelFormatKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	struct cudaChannelFormatDesc cudaCreateChannelDesc(int x, int y, int z, int w, enum cudaChannelFormatKind f) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaCreateChannelDesc)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaCreateChannelDesc = (struct cudaChannelFormatDesc (*)(int, int, int, int, enum cudaChannelFormatKind)) dlsym(libcudart_handle, "cudaCreateChannelDesc");
			fprintf(stderr, "cudaCreateChannelDesc:%p\n", wrapper_cudaCreateChannelDesc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaCreateChannelDesc():%s\n", __dlerror);
			fflush(stderr);
		}
		struct cudaChannelFormatDesc retval = wrapper_cudaCreateChannelDesc(x, y, z, w, f);
		return retval;
	}
}

