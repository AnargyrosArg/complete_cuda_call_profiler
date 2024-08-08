#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBatchNormalizationForwardTrainingEx)(cudnnHandle_t, cudnnBatchNormMode_t, cudnnBatchNormOps_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, const void *, const void *, double, void *, void *, double, void *, void *, cudnnActivationDescriptor_t, void *, size_t, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBatchNormalizationForwardTrainingEx(cudnnHandle_t handle, cudnnBatchNormMode_t mode, cudnnBatchNormOps_t bnOps, const void *alpha, const void *beta, const cudnnTensorDescriptor_t xDesc, const void *xData, const cudnnTensorDescriptor_t zDesc, const void *zData, const cudnnTensorDescriptor_t yDesc, void *yData, const cudnnTensorDescriptor_t bnScaleBiasMeanVarDesc, const void *bnScale, const void *bnBias, double exponentialAverageFactor, void *resultRunningMean, void *resultRunningVariance, double epsilon, void *resultSaveMean, void *resultSaveInvVariance, cudnnActivationDescriptor_t activationDesc, void *workspace, size_t workSpaceSizeInBytes, void *reserveSpace, size_t reserveSpaceSizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBatchNormalizationForwardTrainingEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBatchNormalizationForwardTrainingEx = (cudnnStatus_t (*)(cudnnHandle_t, cudnnBatchNormMode_t, cudnnBatchNormOps_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, const void *, const void *, double, void *, void *, double, void *, void *, cudnnActivationDescriptor_t, void *, size_t, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBatchNormalizationForwardTrainingEx");
			fprintf(stderr, "wrapper_cudnnBatchNormalizationForwardTrainingEx:%p\n", wrapper_cudnnBatchNormalizationForwardTrainingEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBatchNormalizationForwardTrainingEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBatchNormalizationForwardTrainingEx(handle, mode, bnOps, alpha, beta, xDesc, xData, zDesc, zData, yDesc, yData, bnScaleBiasMeanVarDesc, bnScale, bnBias, exponentialAverageFactor, resultRunningMean, resultRunningVariance, epsilon, resultSaveMean, resultSaveInvVariance, activationDesc, workspace, workSpaceSizeInBytes, reserveSpace, reserveSpaceSizeInBytes);
		return retval;
	}
}

