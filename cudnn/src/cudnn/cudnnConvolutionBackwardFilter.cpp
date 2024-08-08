#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnConvolutionBackwardFilter)(cudnnHandle_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, cudnnConvolutionBwdFilterAlgo_t, void *, size_t, const void *, const cudnnFilterDescriptor_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnConvolutionBackwardFilter(cudnnHandle_t handle, const void *alpha, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t dyDesc, const void *dy, const cudnnConvolutionDescriptor_t convDesc, cudnnConvolutionBwdFilterAlgo_t algo, void *workSpace, size_t workSpaceSizeInBytes, const void *beta, const cudnnFilterDescriptor_t dwDesc, void *dw{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnConvolutionBackwardFilter)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnConvolutionBackwardFilter = (cudnnStatus_t (*)(cudnnHandle_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, cudnnConvolutionBwdFilterAlgo_t, void *, size_t, const void *, const cudnnFilterDescriptor_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnConvolutionBackwardFilter");
			fprintf(stderr, "wrapper_cudnnConvolutionBackwardFilter:%p\n", wrapper_cudnnConvolutionBackwardFilter);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnConvolutionBackwardFilter():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnConvolutionBackwardFilter(handle, alpha, xDesc, x, dyDesc, dy, convDesc, algo, workSpace, workSpaceSizeInBytes, beta, dwDesc, dw);
		return retval;
	}
}

