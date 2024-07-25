#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRNNBackwardDataEx)(cudnnHandle_t, const cudnnRNNDescriptor_t, const cudnnRNNDataDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnRNNDataDescriptor_t, void *, void *, size_t, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRNNBackwardDataEx(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const cudnnRNNDataDescriptor_t yDesc, const void *y, const cudnnRNNDataDescriptor_t dyDesc, const void *dy, const cudnnRNNDataDescriptor_t dcDesc, const void *dcAttn, const cudnnTensorDescriptor_t dhyDesc, const void *dhy, const cudnnTensorDescriptor_t dcyDesc, const void *dcy, const cudnnFilterDescriptor_t wDesc, const void *w, const cudnnTensorDescriptor_t hxDesc, const void *hx, const cudnnTensorDescriptor_t cxDesc, const void *cx, const cudnnRNNDataDescriptor_t dxDesc, void *dx, const cudnnTensorDescriptor_t dhxDesc, void *dhx, const cudnnTensorDescriptor_t dcxDesc, void *dcx, const cudnnRNNDataDescriptor_t dkDesc, void *dkeys, void *workSpace, size_t workSpaceSizeInBytes, void *reserveSpace, size_t reserveSpaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRNNBackwardDataEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRNNBackwardDataEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const cudnnRNNDataDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnRNNDataDescriptor_t, void *, void *, size_t, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRNNBackwardDataEx");
			fprintf(stderr, "wrapper_cudnnRNNBackwardDataEx:%p\n", wrapper_cudnnRNNBackwardDataEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRNNBackwardDataEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRNNBackwardDataEx(handle, rnnDesc, yDesc, y, dyDesc, dy, dcDesc, dcAttn, dhyDesc, dhy, dcyDesc, dcy, wDesc, w, hxDesc, hx, cxDesc, cx, dxDesc, dx, dhxDesc, dhx, dcxDesc, dcx, dkDesc, dkeys, workSpace, workSpaceSizeInBytes, reserveSpace, reserveSpaceSizeInBytes);
		return retval;
	}
}

