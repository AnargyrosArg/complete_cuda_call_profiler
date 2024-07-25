#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionBackwardFilterAlgorithmMaxCount)(cudnnHandle_t, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionBackwardFilterAlgorithmMaxCount(cudnnHandle_t handle, int *count) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionBackwardFilterAlgorithmMaxCount)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionBackwardFilterAlgorithmMaxCount = (cudnnStatus_t (*)(cudnnHandle_t, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionBackwardFilterAlgorithmMaxCount");
			fprintf(stderr, "wrapper_cudnnGetConvolutionBackwardFilterAlgorithmMaxCount:%p\n", wrapper_cudnnGetConvolutionBackwardFilterAlgorithmMaxCount);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionBackwardFilterAlgorithmMaxCount():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionBackwardFilterAlgorithmMaxCount(handle, count);
		return retval;
	}
}

