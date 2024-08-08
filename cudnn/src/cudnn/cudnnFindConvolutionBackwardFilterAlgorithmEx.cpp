#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFindConvolutionBackwardFilterAlgorithmEx)(cudnnHandle_t, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, const cudnnFilterDescriptor_t, void *, const int, int *, cudnnConvolutionBwdFilterAlgoPerf_t *, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFindConvolutionBackwardFilterAlgorithmEx(cudnnHandle_t handle, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t dyDesc, const void *y, const cudnnConvolutionDescriptor_t convDesc, const cudnnFilterDescriptor_t dwDesc, void *dw, const int requestedAlgoCount, int *returnedAlgoCount, cudnnConvolutionBwdFilterAlgoPerf_t *perfResults, void *workSpace, size_t workSpaceSizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFindConvolutionBackwardFilterAlgorithmEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFindConvolutionBackwardFilterAlgorithmEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, const cudnnFilterDescriptor_t, void *, const int, int *, cudnnConvolutionBwdFilterAlgoPerf_t *, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFindConvolutionBackwardFilterAlgorithmEx");
			fprintf(stderr, "wrapper_cudnnFindConvolutionBackwardFilterAlgorithmEx:%p\n", wrapper_cudnnFindConvolutionBackwardFilterAlgorithmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFindConvolutionBackwardFilterAlgorithmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFindConvolutionBackwardFilterAlgorithmEx(handle, xDesc, x, dyDesc, y, convDesc, dwDesc, dw, requestedAlgoCount, returnedAlgoCount, perfResults, workSpace, workSpaceSizeInBytes);
		return retval;
	}
}

