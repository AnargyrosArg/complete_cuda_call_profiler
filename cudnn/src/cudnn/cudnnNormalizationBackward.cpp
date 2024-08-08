#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnNormalizationBackward)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const void *, const void *, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, const void *, const void *, void *, void *, double, const cudnnTensorDescriptor_t, const void *, const void *, cudnnActivationDescriptor_t, void *, size_t, void *, size_t, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnNormalizationBackward(cudnnHandle_t handle, cudnnNormMode_t mode, cudnnNormOps_t normOps, cudnnNormAlgo_t algo, const void *alphaDataDiff, const void *betaDataDiff, const void *alphaParamDiff, const void *betaParamDiff, const cudnnTensorDescriptor_t xDesc, const void *xData, const cudnnTensorDescriptor_t yDesc, const void *yData, const cudnnTensorDescriptor_t dyDesc, const void *dyData, const cudnnTensorDescriptor_t dzDesc, void *dzData, const cudnnTensorDescriptor_t dxDesc, void *dxData, const cudnnTensorDescriptor_t dNormScaleBiasDesc, const void *normScaleData, const void *normBiasData, void *dNormScaleData, void *dNormBiasData, double epsilon, const cudnnTensorDescriptor_t normMeanVarDesc, const void *savedMean, const void *savedInvVariance, cudnnActivationDescriptor_t activationDesc, void *workSpace, size_t workSpaceSizeInBytes, void *reserveSpace, size_t reserveSpaceSizeInBytes, int groupCnt{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnNormalizationBackward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnNormalizationBackward = (cudnnStatus_t (*)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const void *, const void *, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, const void *, const void *, void *, void *, double, const cudnnTensorDescriptor_t, const void *, const void *, cudnnActivationDescriptor_t, void *, size_t, void *, size_t, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnNormalizationBackward");
			fprintf(stderr, "wrapper_cudnnNormalizationBackward:%p\n", wrapper_cudnnNormalizationBackward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnNormalizationBackward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnNormalizationBackward(handle, mode, normOps, algo, alphaDataDiff, betaDataDiff, alphaParamDiff, betaParamDiff, xDesc, xData, yDesc, yData, dyDesc, dyData, dzDesc, dzData, dxDesc, dxData, dNormScaleBiasDesc, normScaleData, normBiasData, dNormScaleData, dNormBiasData, epsilon, normMeanVarDesc, savedMean, savedInvVariance, activationDesc, workSpace, workSpaceSizeInBytes, reserveSpace, reserveSpaceSizeInBytes, groupCnt);
		return retval;
	}
}

