#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFindConvolutionBackwardFilterAlgorithm)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnFilterDescriptor_t, const int, int *, cudnnConvolutionBwdFilterAlgoPerf_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFindConvolutionBackwardFilterAlgorithm(cudnnHandle_t handle, const cudnnTensorDescriptor_t xDesc, const cudnnTensorDescriptor_t dyDesc, const cudnnConvolutionDescriptor_t convDesc, const cudnnFilterDescriptor_t dwDesc, const int requestedAlgoCount, int *returnedAlgoCount, cudnnConvolutionBwdFilterAlgoPerf_t *perfResults){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFindConvolutionBackwardFilterAlgorithm)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFindConvolutionBackwardFilterAlgorithm = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnFilterDescriptor_t, const int, int *, cudnnConvolutionBwdFilterAlgoPerf_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFindConvolutionBackwardFilterAlgorithm");
			fprintf(stderr, "wrapper_cudnnFindConvolutionBackwardFilterAlgorithm:%p\n", wrapper_cudnnFindConvolutionBackwardFilterAlgorithm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFindConvolutionBackwardFilterAlgorithm():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFindConvolutionBackwardFilterAlgorithm(handle, xDesc, dyDesc, convDesc, dwDesc, requestedAlgoCount, returnedAlgoCount, perfResults);
		return retval;
	}
}

