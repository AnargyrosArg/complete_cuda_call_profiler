#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetTensorNdDescriptor)(const cudnnTensorDescriptor_t, int, cudnnDataType_t *, int *, int *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetTensorNdDescriptor(const cudnnTensorDescriptor_t tensorDesc, int nbDimsRequested, cudnnDataType_t *dataType, int *nbDims, int dimA[], int strideA[]{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetTensorNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetTensorNdDescriptor = (cudnnStatus_t (*)(const cudnnTensorDescriptor_t, int, cudnnDataType_t *, int *, int *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetTensorNdDescriptor");
			fprintf(stderr, "wrapper_cudnnGetTensorNdDescriptor:%p\n", wrapper_cudnnGetTensorNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetTensorNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetTensorNdDescriptor(tensorDesc, nbDimsRequested, dataType, nbDims, dimA, strideA);
		return retval;
	}
}

