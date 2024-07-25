#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnReorderFilterAndBias)(cudnnHandle_t, const cudnnFilterDescriptor_t, cudnnReorderType_t, const void *, void *, int, const void *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnReorderFilterAndBias(cudnnHandle_t handle, const cudnnFilterDescriptor_t filterDesc, cudnnReorderType_t reorderType, const void *filterData, void *reorderedFilterData, int reorderBias, const void *biasData, void *reorderedBiasData) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnReorderFilterAndBias)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnReorderFilterAndBias = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnFilterDescriptor_t, cudnnReorderType_t, const void *, void *, int, const void *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnReorderFilterAndBias");
			fprintf(stderr, "wrapper_cudnnReorderFilterAndBias:%p\n", wrapper_cudnnReorderFilterAndBias);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnReorderFilterAndBias():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnReorderFilterAndBias(handle, filterDesc, reorderType, filterData, reorderedFilterData, reorderBias, biasData, reorderedBiasData);
		return retval;
	}
}

