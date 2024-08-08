#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetTensor4dDescriptor)(cudnnTensorDescriptor_t, cudnnTensorFormat_t, cudnnDataType_t, int, int, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetTensor4dDescriptor(cudnnTensorDescriptor_t tensorDesc, cudnnTensorFormat_t format, cudnnDataType_t dataType, int n, int c, int h, int w{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetTensor4dDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetTensor4dDescriptor = (cudnnStatus_t (*)(cudnnTensorDescriptor_t, cudnnTensorFormat_t, cudnnDataType_t, int, int, int, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetTensor4dDescriptor");
			fprintf(stderr, "wrapper_cudnnSetTensor4dDescriptor:%p\n", wrapper_cudnnSetTensor4dDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetTensor4dDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetTensor4dDescriptor(tensorDesc, format, dataType, n, c, h, w);
		return retval;
	}
}

