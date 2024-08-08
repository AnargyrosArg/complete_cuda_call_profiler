#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetSeqDataDescriptor)(const cudnnSeqDataDescriptor_t, cudnnDataType_t *, int *, int, int *, cudnnSeqDataAxis_t *, size_t *, size_t, int *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetSeqDataDescriptor(const cudnnSeqDataDescriptor_t seqDataDesc, cudnnDataType_t *dataType, int *nbDims, int nbDimsRequested, int dimA[], cudnnSeqDataAxis_t axes[], size_t *seqLengthArraySize, size_t seqLengthSizeRequested, int seqLengthArray[], void *paddingFill){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetSeqDataDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetSeqDataDescriptor = (cudnnStatus_t (*)(const cudnnSeqDataDescriptor_t, cudnnDataType_t *, int *, int, int *, cudnnSeqDataAxis_t *, size_t *, size_t, int *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetSeqDataDescriptor");
			fprintf(stderr, "wrapper_cudnnGetSeqDataDescriptor:%p\n", wrapper_cudnnGetSeqDataDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetSeqDataDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetSeqDataDescriptor(seqDataDesc, dataType, nbDims, nbDimsRequested, dimA, axes, seqLengthArraySize, seqLengthSizeRequested, seqLengthArray, paddingFill);
		return retval;
	}
}

