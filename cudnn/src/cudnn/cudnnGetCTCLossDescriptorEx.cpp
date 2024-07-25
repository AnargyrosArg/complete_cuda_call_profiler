#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetCTCLossDescriptorEx)(cudnnCTCLossDescriptor_t, cudnnDataType_t *, cudnnLossNormalizationMode_t *, cudnnNanPropagation_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetCTCLossDescriptorEx(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t *compType, cudnnLossNormalizationMode_t *normMode, cudnnNanPropagation_t *gradMode) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetCTCLossDescriptorEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetCTCLossDescriptorEx = (cudnnStatus_t (*)(cudnnCTCLossDescriptor_t, cudnnDataType_t *, cudnnLossNormalizationMode_t *, cudnnNanPropagation_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetCTCLossDescriptorEx");
			fprintf(stderr, "wrapper_cudnnGetCTCLossDescriptorEx:%p\n", wrapper_cudnnGetCTCLossDescriptorEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetCTCLossDescriptorEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetCTCLossDescriptorEx(ctcLossDesc, compType, normMode, gradMode);
		return retval;
	}
}

