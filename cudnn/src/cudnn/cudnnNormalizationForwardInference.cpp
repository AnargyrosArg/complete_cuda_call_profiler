#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnNormalizationForwardInference)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, void *, double, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnNormalizationForwardInference(cudnnHandle_t handle, cudnnNormMode_t mode, cudnnNormOps_t normOps, cudnnNormAlgo_t algo, const void *alpha, const void *beta, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t normScaleBiasDesc, const void *normScale, const void *normBias, const cudnnTensorDescriptor_t normMeanVarDesc, const void *estimatedMean, const void *estimatedVariance, const cudnnTensorDescriptor_t zDesc, const void *z, cudnnActivationDescriptor_t activationDesc, const cudnnTensorDescriptor_t yDesc, void *y, double epsilon, int groupCnt{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnNormalizationForwardInference)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnNormalizationForwardInference = (cudnnStatus_t (*)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, void *, double, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnNormalizationForwardInference");
			fprintf(stderr, "wrapper_cudnnNormalizationForwardInference:%p\n", wrapper_cudnnNormalizationForwardInference);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnNormalizationForwardInference():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnNormalizationForwardInference(handle, mode, normOps, algo, alpha, beta, xDesc, x, normScaleBiasDesc, normScale, normBias, normMeanVarDesc, estimatedMean, estimatedVariance, zDesc, z, activationDesc, yDesc, y, epsilon, groupCnt);
		return retval;
	}
}

