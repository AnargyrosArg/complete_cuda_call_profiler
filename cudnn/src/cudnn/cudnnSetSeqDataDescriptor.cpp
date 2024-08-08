#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetSeqDataDescriptor)(cudnnSeqDataDescriptor_t, cudnnDataType_t, int, const int *, const cudnnSeqDataAxis_t *, size_t, const int *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetSeqDataDescriptor(cudnnSeqDataDescriptor_t seqDataDesc, cudnnDataType_t dataType, int nbDims, const int dimA[], const cudnnSeqDataAxis_t axes[], size_t seqLengthArraySize, const int seqLengthArray[], void *paddingFill{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetSeqDataDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetSeqDataDescriptor = (cudnnStatus_t (*)(cudnnSeqDataDescriptor_t, cudnnDataType_t, int, const int *, const cudnnSeqDataAxis_t *, size_t, const int *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetSeqDataDescriptor");
			fprintf(stderr, "wrapper_cudnnSetSeqDataDescriptor:%p\n", wrapper_cudnnSetSeqDataDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetSeqDataDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetSeqDataDescriptor(seqDataDesc, dataType, nbDims, dimA, axes, seqLengthArraySize, seqLengthArray, paddingFill);
		return retval;
	}
}

