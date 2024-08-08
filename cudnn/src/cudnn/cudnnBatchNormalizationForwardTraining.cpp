#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBatchNormalizationForwardTraining)(cudnnHandle_t, cudnnBatchNormMode_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, const void *, const void *, double, void *, void *, double, void *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBatchNormalizationForwardTraining(cudnnHandle_t handle, cudnnBatchNormMode_t mode, const void *alpha, const void *beta, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t yDesc, void *y, const cudnnTensorDescriptor_t bnScaleBiasMeanVarDesc, const void *bnScale, const void *bnBias, double exponentialAverageFactor, void *resultRunningMean, void *resultRunningVariance, double epsilon, void *resultSaveMean, void *resultSaveInvVariance{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBatchNormalizationForwardTraining)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBatchNormalizationForwardTraining = (cudnnStatus_t (*)(cudnnHandle_t, cudnnBatchNormMode_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, const void *, const void *, double, void *, void *, double, void *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBatchNormalizationForwardTraining");
			fprintf(stderr, "wrapper_cudnnBatchNormalizationForwardTraining:%p\n", wrapper_cudnnBatchNormalizationForwardTraining);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBatchNormalizationForwardTraining():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBatchNormalizationForwardTraining(handle, mode, alpha, beta, xDesc, x, yDesc, y, bnScaleBiasMeanVarDesc, bnScale, bnBias, exponentialAverageFactor, resultRunningMean, resultRunningVariance, epsilon, resultSaveMean, resultSaveInvVariance);
		return retval;
	}
}

