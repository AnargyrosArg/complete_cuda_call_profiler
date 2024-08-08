#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnOpTensor)(cudnnHandle_t, const cudnnOpTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnOpTensor(cudnnHandle_t handle, const cudnnOpTensorDescriptor_t opTensorDesc, const void *alpha1, const cudnnTensorDescriptor_t aDesc, const void *A, const void *alpha2, const cudnnTensorDescriptor_t bDesc, const void *B, const void *beta, const cudnnTensorDescriptor_t cDesc, void *C){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnOpTensor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnOpTensor = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnOpTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnOpTensor");
			fprintf(stderr, "wrapper_cudnnOpTensor:%p\n", wrapper_cudnnOpTensor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnOpTensor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnOpTensor(handle, opTensorDesc, alpha1, aDesc, A, alpha2, bDesc, B, beta, cDesc, C);
		return retval;
	}
}

