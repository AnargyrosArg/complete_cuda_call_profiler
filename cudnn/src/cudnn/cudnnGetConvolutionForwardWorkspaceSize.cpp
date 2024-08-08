#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionForwardWorkspaceSize)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, cudnnConvolutionFwdAlgo_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionForwardWorkspaceSize(cudnnHandle_t handle, const cudnnTensorDescriptor_t xDesc, const cudnnFilterDescriptor_t wDesc, const cudnnConvolutionDescriptor_t convDesc, const cudnnTensorDescriptor_t yDesc, cudnnConvolutionFwdAlgo_t algo, size_t *sizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionForwardWorkspaceSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionForwardWorkspaceSize = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, cudnnConvolutionFwdAlgo_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionForwardWorkspaceSize");
			fprintf(stderr, "wrapper_cudnnGetConvolutionForwardWorkspaceSize:%p\n", wrapper_cudnnGetConvolutionForwardWorkspaceSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionForwardWorkspaceSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionForwardWorkspaceSize(handle, xDesc, wDesc, convDesc, yDesc, algo, sizeInBytes);
		return retval;
	}
}

