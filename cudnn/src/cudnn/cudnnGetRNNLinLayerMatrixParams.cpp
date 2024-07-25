#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNLinLayerMatrixParams)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, const void *, const int, cudnnFilterDescriptor_t, void **);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNLinLayerMatrixParams(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const int pseudoLayer, const cudnnTensorDescriptor_t xDesc, const cudnnFilterDescriptor_t wDesc, const void *w, const int linLayerID, cudnnFilterDescriptor_t linLayerMatDesc, void **linLayerMat) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNLinLayerMatrixParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNLinLayerMatrixParams = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, const void *, const int, cudnnFilterDescriptor_t, void **)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNLinLayerMatrixParams");
			fprintf(stderr, "wrapper_cudnnGetRNNLinLayerMatrixParams:%p\n", wrapper_cudnnGetRNNLinLayerMatrixParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNLinLayerMatrixParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNLinLayerMatrixParams(handle, rnnDesc, pseudoLayer, xDesc, wDesc, w, linLayerID, linLayerMatDesc, linLayerMat);
		return retval;
	}
}

