#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetStream)(cudnnHandle_t, cudaStream_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetStream(cudnnHandle_t handle, cudaStream_t *streamId) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetStream)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetStream = (cudnnStatus_t (*)(cudnnHandle_t, cudaStream_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetStream");
			fprintf(stderr, "wrapper_cudnnGetStream:%p\n", wrapper_cudnnGetStream);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetStream():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetStream(handle, streamId);
		return retval;
	}
}

