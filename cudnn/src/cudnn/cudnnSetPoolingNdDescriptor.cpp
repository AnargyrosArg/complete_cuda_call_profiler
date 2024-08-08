#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetPoolingNdDescriptor)(cudnnPoolingDescriptor_t, const cudnnPoolingMode_t, const cudnnNanPropagation_t, int, const int *, const int *, const int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetPoolingNdDescriptor(cudnnPoolingDescriptor_t poolingDesc, const cudnnPoolingMode_t mode, const cudnnNanPropagation_t maxpoolingNanOpt, int nbDims, const int windowDimA[], const int paddingA[], const int strideA[]{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetPoolingNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetPoolingNdDescriptor = (cudnnStatus_t (*)(cudnnPoolingDescriptor_t, const cudnnPoolingMode_t, const cudnnNanPropagation_t, int, const int *, const int *, const int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetPoolingNdDescriptor");
			fprintf(stderr, "wrapper_cudnnSetPoolingNdDescriptor:%p\n", wrapper_cudnnSetPoolingNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetPoolingNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetPoolingNdDescriptor(poolingDesc, mode, maxpoolingNanOpt, nbDims, windowDimA, paddingA, strideA);
		return retval;
	}
}

