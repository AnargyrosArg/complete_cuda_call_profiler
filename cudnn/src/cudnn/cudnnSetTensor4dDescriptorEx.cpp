#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetTensor4dDescriptorEx)(cudnnTensorDescriptor_t, cudnnDataType_t, int, int, int, int, int, int, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetTensor4dDescriptorEx(cudnnTensorDescriptor_t tensorDesc, cudnnDataType_t dataType, int n, int c, int h, int w, int nStride, int cStride, int hStride, int wStride{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetTensor4dDescriptorEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetTensor4dDescriptorEx = (cudnnStatus_t (*)(cudnnTensorDescriptor_t, cudnnDataType_t, int, int, int, int, int, int, int, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetTensor4dDescriptorEx");
			fprintf(stderr, "wrapper_cudnnSetTensor4dDescriptorEx:%p\n", wrapper_cudnnSetTensor4dDescriptorEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetTensor4dDescriptorEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetTensor4dDescriptorEx(tensorDesc, dataType, n, c, h, w, nStride, cStride, hStride, wStride);
		return retval;
	}
}

