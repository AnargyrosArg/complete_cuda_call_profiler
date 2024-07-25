#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionBackwardFilterAlgorithm_v7)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnFilterDescriptor_t, const int, int *, cudnnConvolutionBwdFilterAlgoPerf_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionBackwardFilterAlgorithm_v7(cudnnHandle_t handle, const cudnnTensorDescriptor_t srcDesc, const cudnnTensorDescriptor_t diffDesc, const cudnnConvolutionDescriptor_t convDesc, const cudnnFilterDescriptor_t gradDesc, const int requestedAlgoCount, int *returnedAlgoCount, cudnnConvolutionBwdFilterAlgoPerf_t *perfResults) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionBackwardFilterAlgorithm_v7)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionBackwardFilterAlgorithm_v7 = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnFilterDescriptor_t, const int, int *, cudnnConvolutionBwdFilterAlgoPerf_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionBackwardFilterAlgorithm_v7");
			fprintf(stderr, "wrapper_cudnnGetConvolutionBackwardFilterAlgorithm_v7:%p\n", wrapper_cudnnGetConvolutionBackwardFilterAlgorithm_v7);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionBackwardFilterAlgorithm_v7():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionBackwardFilterAlgorithm_v7(handle, srcDesc, diffDesc, convDesc, gradDesc, requestedAlgoCount, returnedAlgoCount, perfResults);
		return retval;
	}
}

