#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRNNForward)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnForwardMode_t, const int32_t *, cudnnRNNDataDescriptor_t, const void *, cudnnRNNDataDescriptor_t, void *, cudnnTensorDescriptor_t, const void *, void *, cudnnTensorDescriptor_t, const void *, void *, size_t, const void *, size_t, void *, size_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRNNForward(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, cudnnForwardMode_t fwdMode, const int32_t devSeqLengths[], cudnnRNNDataDescriptor_t xDesc, const void *x, cudnnRNNDataDescriptor_t yDesc, void *y, cudnnTensorDescriptor_t hDesc, const void *hx, void *hy, cudnnTensorDescriptor_t cDesc, const void *cx, void *cy, size_t weightSpaceSize, const void *weightSpace, size_t workSpaceSize, void *workSpace, size_t reserveSpaceSize, void *reserveSpace{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRNNForward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRNNForward = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnForwardMode_t, const int32_t *, cudnnRNNDataDescriptor_t, const void *, cudnnRNNDataDescriptor_t, void *, cudnnTensorDescriptor_t, const void *, void *, cudnnTensorDescriptor_t, const void *, void *, size_t, const void *, size_t, void *, size_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRNNForward");
			fprintf(stderr, "wrapper_cudnnRNNForward:%p\n", wrapper_cudnnRNNForward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRNNForward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRNNForward(handle, rnnDesc, fwdMode, devSeqLengths, xDesc, x, yDesc, y, hDesc, hx, hy, cDesc, cx, cy, weightSpaceSize, weightSpace, workSpaceSize, workSpace, reserveSpaceSize, reserveSpace);
		return retval;
	}
}

