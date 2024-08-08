#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetNormalizationTrainingReserveSpaceSize)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, size_t *, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetNormalizationTrainingReserveSpaceSize(cudnnHandle_t handle, cudnnNormMode_t mode, cudnnNormOps_t normOps, cudnnNormAlgo_t algo, const cudnnActivationDescriptor_t activationDesc, const cudnnTensorDescriptor_t xDesc, size_t *sizeInBytes, int groupCnt){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetNormalizationTrainingReserveSpaceSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetNormalizationTrainingReserveSpaceSize = (cudnnStatus_t (*)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, size_t *, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetNormalizationTrainingReserveSpaceSize");
			fprintf(stderr, "wrapper_cudnnGetNormalizationTrainingReserveSpaceSize:%p\n", wrapper_cudnnGetNormalizationTrainingReserveSpaceSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetNormalizationTrainingReserveSpaceSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetNormalizationTrainingReserveSpaceSize(handle, mode, normOps, algo, activationDesc, xDesc, sizeInBytes, groupCnt);
		return retval;
	}
}

