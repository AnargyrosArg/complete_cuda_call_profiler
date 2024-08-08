#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetFilterNdDescriptor)(cudnnFilterDescriptor_t, cudnnDataType_t, cudnnTensorFormat_t, int, const int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetFilterNdDescriptor(cudnnFilterDescriptor_t filterDesc, cudnnDataType_t dataType, cudnnTensorFormat_t format, int nbDims, const int filterDimA[]{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetFilterNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetFilterNdDescriptor = (cudnnStatus_t (*)(cudnnFilterDescriptor_t, cudnnDataType_t, cudnnTensorFormat_t, int, const int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetFilterNdDescriptor");
			fprintf(stderr, "wrapper_cudnnSetFilterNdDescriptor:%p\n", wrapper_cudnnSetFilterNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetFilterNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetFilterNdDescriptor(filterDesc, dataType, format, nbDims, filterDimA);
		return retval;
	}
}

