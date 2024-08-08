#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionBackwardFilterWorkspaceSize)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnFilterDescriptor_t, cudnnConvolutionBwdFilterAlgo_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionBackwardFilterWorkspaceSize(cudnnHandle_t handle, const cudnnTensorDescriptor_t xDesc, const cudnnTensorDescriptor_t dyDesc, const cudnnConvolutionDescriptor_t convDesc, const cudnnFilterDescriptor_t gradDesc, cudnnConvolutionBwdFilterAlgo_t algo, size_t *sizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionBackwardFilterWorkspaceSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionBackwardFilterWorkspaceSize = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnFilterDescriptor_t, cudnnConvolutionBwdFilterAlgo_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionBackwardFilterWorkspaceSize");
			fprintf(stderr, "wrapper_cudnnGetConvolutionBackwardFilterWorkspaceSize:%p\n", wrapper_cudnnGetConvolutionBackwardFilterWorkspaceSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionBackwardFilterWorkspaceSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionBackwardFilterWorkspaceSize(handle, xDesc, dyDesc, convDesc, gradDesc, algo, sizeInBytes);
		return retval;
	}
}

