#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionForwardAlgorithm_v7)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, const int, int *, cudnnConvolutionFwdAlgoPerf_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionForwardAlgorithm_v7(cudnnHandle_t handle, const cudnnTensorDescriptor_t srcDesc, const cudnnFilterDescriptor_t filterDesc, const cudnnConvolutionDescriptor_t convDesc, const cudnnTensorDescriptor_t destDesc, const int requestedAlgoCount, int *returnedAlgoCount, cudnnConvolutionFwdAlgoPerf_t *perfResults) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionForwardAlgorithm_v7)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionForwardAlgorithm_v7 = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, const int, int *, cudnnConvolutionFwdAlgoPerf_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionForwardAlgorithm_v7");
			fprintf(stderr, "wrapper_cudnnGetConvolutionForwardAlgorithm_v7:%p\n", wrapper_cudnnGetConvolutionForwardAlgorithm_v7);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionForwardAlgorithm_v7():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionForwardAlgorithm_v7(handle, srcDesc, filterDesc, convDesc, destDesc, requestedAlgoCount, returnedAlgoCount, perfResults);
		return retval;
	}
}

