#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetTensorNdDescriptorEx)(cudnnTensorDescriptor_t, cudnnTensorFormat_t, cudnnDataType_t, int, const int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetTensorNdDescriptorEx(cudnnTensorDescriptor_t tensorDesc, cudnnTensorFormat_t format, cudnnDataType_t dataType, int nbDims, const int dimA[]){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetTensorNdDescriptorEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetTensorNdDescriptorEx = (cudnnStatus_t (*)(cudnnTensorDescriptor_t, cudnnTensorFormat_t, cudnnDataType_t, int, const int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetTensorNdDescriptorEx");
			fprintf(stderr, "wrapper_cudnnSetTensorNdDescriptorEx:%p\n", wrapper_cudnnSetTensorNdDescriptorEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetTensorNdDescriptorEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetTensorNdDescriptorEx(tensorDesc, format, dataType, nbDims, dimA);
		return retval;
	}
}

