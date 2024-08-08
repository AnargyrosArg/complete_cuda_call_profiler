#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnNormalizationForwardTraining)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, double, const cudnnTensorDescriptor_t, void *, void *, double, void *, void *, cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, void *, size_t, void *, size_t, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnNormalizationForwardTraining(cudnnHandle_t handle, cudnnNormMode_t mode, cudnnNormOps_t normOps, cudnnNormAlgo_t algo, const void *alpha, const void *beta, const cudnnTensorDescriptor_t xDesc, const void *xData, const cudnnTensorDescriptor_t normScaleBiasDesc, const void *normScale, const void *normBias, double exponentialAverageFactor, const cudnnTensorDescriptor_t normMeanVarDesc, void *resultRunningMean, void *resultRunningVariance, double epsilon, void *resultSaveMean, void *resultSaveInvVariance, cudnnActivationDescriptor_t activationDesc, const cudnnTensorDescriptor_t zDesc, const void *zData, const cudnnTensorDescriptor_t yDesc, void *yData, void *workspace, size_t workSpaceSizeInBytes, void *reserveSpace, size_t reserveSpaceSizeInBytes, int groupCnt{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnNormalizationForwardTraining)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnNormalizationForwardTraining = (cudnnStatus_t (*)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, double, const cudnnTensorDescriptor_t, void *, void *, double, void *, void *, cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, void *, size_t, void *, size_t, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnNormalizationForwardTraining");
			fprintf(stderr, "wrapper_cudnnNormalizationForwardTraining:%p\n", wrapper_cudnnNormalizationForwardTraining);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnNormalizationForwardTraining():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnNormalizationForwardTraining(handle, mode, normOps, algo, alpha, beta, xDesc, xData, normScaleBiasDesc, normScale, normBias, exponentialAverageFactor, normMeanVarDesc, resultRunningMean, resultRunningVariance, epsilon, resultSaveMean, resultSaveInvVariance, activationDesc, zDesc, zData, yDesc, yData, workspace, workSpaceSizeInBytes, reserveSpace, reserveSpaceSizeInBytes, groupCnt);
		return retval;
	}
}

