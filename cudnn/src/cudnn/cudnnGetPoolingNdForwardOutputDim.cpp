#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetPoolingNdForwardOutputDim)(const cudnnPoolingDescriptor_t, const cudnnTensorDescriptor_t, int, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetPoolingNdForwardOutputDim(const cudnnPoolingDescriptor_t poolingDesc, const cudnnTensorDescriptor_t inputTensorDesc, int nbDims, int outputTensorDimA[]{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetPoolingNdForwardOutputDim)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetPoolingNdForwardOutputDim = (cudnnStatus_t (*)(const cudnnPoolingDescriptor_t, const cudnnTensorDescriptor_t, int, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetPoolingNdForwardOutputDim");
			fprintf(stderr, "wrapper_cudnnGetPoolingNdForwardOutputDim:%p\n", wrapper_cudnnGetPoolingNdForwardOutputDim);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetPoolingNdForwardOutputDim():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetPoolingNdForwardOutputDim(poolingDesc, inputTensorDesc, nbDims, outputTensorDimA);
		return retval;
	}
}

