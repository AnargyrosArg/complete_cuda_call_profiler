#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNParamsSize)(cudnnHandle_t, const cudnnRNNDescriptor_t, const cudnnTensorDescriptor_t, size_t *, cudnnDataType_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNParamsSize(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const cudnnTensorDescriptor_t xDesc, size_t *sizeInBytes, cudnnDataType_t dataType{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNParamsSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNParamsSize = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const cudnnTensorDescriptor_t, size_t *, cudnnDataType_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNParamsSize");
			fprintf(stderr, "wrapper_cudnnGetRNNParamsSize:%p\n", wrapper_cudnnGetRNNParamsSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNParamsSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNParamsSize(handle, rnnDesc, xDesc, sizeInBytes, dataType);
		return retval;
	}
}

