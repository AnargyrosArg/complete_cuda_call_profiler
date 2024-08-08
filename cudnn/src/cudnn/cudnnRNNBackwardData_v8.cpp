#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRNNBackwardData_v8)(cudnnHandle_t, cudnnRNNDescriptor_t, const int32_t *, cudnnRNNDataDescriptor_t, const void *, const void *, cudnnRNNDataDescriptor_t, void *, cudnnTensorDescriptor_t, const void *, const void *, void *, cudnnTensorDescriptor_t, const void *, const void *, void *, size_t, const void *, size_t, void *, size_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRNNBackwardData_v8(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, const int32_t devSeqLengths[], cudnnRNNDataDescriptor_t yDesc, const void *y, const void *dy, cudnnRNNDataDescriptor_t xDesc, void *dx, cudnnTensorDescriptor_t hDesc, const void *hx, const void *dhy, void *dhx, cudnnTensorDescriptor_t cDesc, const void *cx, const void *dcy, void *dcx, size_t weightSpaceSize, const void *weightSpace, size_t workSpaceSize, void *workSpace, size_t reserveSpaceSize, void *reserveSpace){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRNNBackwardData_v8)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRNNBackwardData_v8 = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, const int32_t *, cudnnRNNDataDescriptor_t, const void *, const void *, cudnnRNNDataDescriptor_t, void *, cudnnTensorDescriptor_t, const void *, const void *, void *, cudnnTensorDescriptor_t, const void *, const void *, void *, size_t, const void *, size_t, void *, size_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRNNBackwardData_v8");
			fprintf(stderr, "wrapper_cudnnRNNBackwardData_v8:%p\n", wrapper_cudnnRNNBackwardData_v8);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRNNBackwardData_v8():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRNNBackwardData_v8(handle, rnnDesc, devSeqLengths, yDesc, y, dy, xDesc, dx, hDesc, hx, dhy, dhx, cDesc, cx, dcy, dcx, weightSpaceSize, weightSpace, workSpaceSize, workSpace, reserveSpaceSize, reserveSpace);
		return retval;
	}
}

