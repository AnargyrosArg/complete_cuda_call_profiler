#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNLinLayerBiasParams)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, const void *, const int, cudnnFilterDescriptor_t, void **);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNLinLayerBiasParams(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const int pseudoLayer, const cudnnTensorDescriptor_t xDesc, const cudnnFilterDescriptor_t wDesc, const void *w, const int linLayerID, cudnnFilterDescriptor_t linLayerBiasDesc, void **linLayerBias) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNLinLayerBiasParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNLinLayerBiasParams = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, const void *, const int, cudnnFilterDescriptor_t, void **)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNLinLayerBiasParams");
			fprintf(stderr, "wrapper_cudnnGetRNNLinLayerBiasParams:%p\n", wrapper_cudnnGetRNNLinLayerBiasParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNLinLayerBiasParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNLinLayerBiasParams(handle, rnnDesc, pseudoLayer, xDesc, wDesc, w, linLayerID, linLayerBiasDesc, linLayerBias);
		return retval;
	}
}

