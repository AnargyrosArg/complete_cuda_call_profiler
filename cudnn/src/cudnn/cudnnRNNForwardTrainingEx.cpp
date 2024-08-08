#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRNNForwardTrainingEx)(cudnnHandle_t, const cudnnRNNDescriptor_t, const cudnnRNNDataDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnRNNDataDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, void *, const cudnnRNNDataDescriptor_t, void *, const cudnnRNNDataDescriptor_t, void *, void *, size_t, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRNNForwardTrainingEx(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const cudnnRNNDataDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t hxDesc, const void *hx, const cudnnTensorDescriptor_t cxDesc, const void *cx, const cudnnFilterDescriptor_t wDesc, const void *w, const cudnnRNNDataDescriptor_t yDesc, void *y, const cudnnTensorDescriptor_t hyDesc, void *hy, const cudnnTensorDescriptor_t cyDesc, void *cy, const cudnnRNNDataDescriptor_t kDesc, const void *keys, const cudnnRNNDataDescriptor_t cDesc, void *cAttn, const cudnnRNNDataDescriptor_t iDesc, void *iAttn, const cudnnRNNDataDescriptor_t qDesc, void *queries, void *workSpace, size_t workSpaceSizeInBytes, void *reserveSpace, size_t reserveSpaceSizeInBytes{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRNNForwardTrainingEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRNNForwardTrainingEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const cudnnRNNDataDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const cudnnRNNDataDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, void *, const cudnnRNNDataDescriptor_t, void *, const cudnnRNNDataDescriptor_t, void *, void *, size_t, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRNNForwardTrainingEx");
			fprintf(stderr, "wrapper_cudnnRNNForwardTrainingEx:%p\n", wrapper_cudnnRNNForwardTrainingEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRNNForwardTrainingEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRNNForwardTrainingEx(handle, rnnDesc, xDesc, x, hxDesc, hx, cxDesc, cx, wDesc, w, yDesc, y, hyDesc, hy, cyDesc, cy, kDesc, keys, cDesc, cAttn, iDesc, iAttn, qDesc, queries, workSpace, workSpaceSizeInBytes, reserveSpace, reserveSpaceSizeInBytes);
		return retval;
	}
}

