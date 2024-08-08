#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnConvolutionBiasActivationForward)(cudnnHandle_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, cudnnConvolutionFwdAlgo_t, void *, size_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnConvolutionBiasActivationForward(cudnnHandle_t handle, const void *alpha1, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnFilterDescriptor_t wDesc, const void *w, const cudnnConvolutionDescriptor_t convDesc, cudnnConvolutionFwdAlgo_t algo, void *workSpace, size_t workSpaceSizeInBytes, const void *alpha2, const cudnnTensorDescriptor_t zDesc, const void *z, const cudnnTensorDescriptor_t biasDesc, const void *bias, const cudnnActivationDescriptor_t activationDesc, const cudnnTensorDescriptor_t yDesc, void *y){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnConvolutionBiasActivationForward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnConvolutionBiasActivationForward = (cudnnStatus_t (*)(cudnnHandle_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, cudnnConvolutionFwdAlgo_t, void *, size_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnConvolutionBiasActivationForward");
			fprintf(stderr, "wrapper_cudnnConvolutionBiasActivationForward:%p\n", wrapper_cudnnConvolutionBiasActivationForward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnConvolutionBiasActivationForward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnConvolutionBiasActivationForward(handle, alpha1, xDesc, x, wDesc, w, convDesc, algo, workSpace, workSpaceSizeInBytes, alpha2, zDesc, z, biasDesc, bias, activationDesc, yDesc, y);
		return retval;
	}
}

