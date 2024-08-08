#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetTensor)(cudnnHandle_t, const cudnnTensorDescriptor_t, void *, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetTensor(cudnnHandle_t handle, const cudnnTensorDescriptor_t yDesc, void *y, const void *valuePtr){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetTensor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetTensor = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, void *, const void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetTensor");
			fprintf(stderr, "wrapper_cudnnSetTensor:%p\n", wrapper_cudnnSetTensor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetTensor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetTensor(handle, yDesc, y, valuePtr);
		return retval;
	}
}

