#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetTensorNdDescriptor)(cudnnTensorDescriptor_t, cudnnDataType_t, int, const int *, const int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetTensorNdDescriptor(cudnnTensorDescriptor_t tensorDesc, cudnnDataType_t dataType, int nbDims, const int dimA[], const int strideA[]{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetTensorNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetTensorNdDescriptor = (cudnnStatus_t (*)(cudnnTensorDescriptor_t, cudnnDataType_t, int, const int *, const int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetTensorNdDescriptor");
			fprintf(stderr, "wrapper_cudnnSetTensorNdDescriptor:%p\n", wrapper_cudnnSetTensorNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetTensorNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetTensorNdDescriptor(tensorDesc, dataType, nbDims, dimA, strideA);
		return retval;
	}
}

