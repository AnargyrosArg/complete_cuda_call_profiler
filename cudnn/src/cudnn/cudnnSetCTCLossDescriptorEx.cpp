#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetCTCLossDescriptorEx)(cudnnCTCLossDescriptor_t, cudnnDataType_t, cudnnLossNormalizationMode_t, cudnnNanPropagation_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetCTCLossDescriptorEx(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t compType, cudnnLossNormalizationMode_t normMode, cudnnNanPropagation_t gradMode) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetCTCLossDescriptorEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetCTCLossDescriptorEx = (cudnnStatus_t (*)(cudnnCTCLossDescriptor_t, cudnnDataType_t, cudnnLossNormalizationMode_t, cudnnNanPropagation_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetCTCLossDescriptorEx");
			fprintf(stderr, "wrapper_cudnnSetCTCLossDescriptorEx:%p\n", wrapper_cudnnSetCTCLossDescriptorEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetCTCLossDescriptorEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetCTCLossDescriptorEx(ctcLossDesc, compType, normMode, gradMode);
		return retval;
	}
}

