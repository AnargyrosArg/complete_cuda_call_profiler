#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionForwardAlgorithmMaxCount)(cudnnHandle_t, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionForwardAlgorithmMaxCount(cudnnHandle_t handle, int *count) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionForwardAlgorithmMaxCount)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionForwardAlgorithmMaxCount = (cudnnStatus_t (*)(cudnnHandle_t, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionForwardAlgorithmMaxCount");
			fprintf(stderr, "wrapper_cudnnGetConvolutionForwardAlgorithmMaxCount:%p\n", wrapper_cudnnGetConvolutionForwardAlgorithmMaxCount);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionForwardAlgorithmMaxCount():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionForwardAlgorithmMaxCount(handle, count);
		return retval;
	}
}

