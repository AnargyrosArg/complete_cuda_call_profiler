#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNDataDescriptor)(cudnnRNNDataDescriptor_t, cudnnDataType_t *, cudnnRNNDataLayout_t *, int *, int *, int *, int, int *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNDataDescriptor(cudnnRNNDataDescriptor_t rnnDataDesc, cudnnDataType_t *dataType, cudnnRNNDataLayout_t *layout, int *maxSeqLength, int *batchSize, int *vectorSize, int arrayLengthRequested, int seqLengthArray[], void *paddingFill) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNDataDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNDataDescriptor = (cudnnStatus_t (*)(cudnnRNNDataDescriptor_t, cudnnDataType_t *, cudnnRNNDataLayout_t *, int *, int *, int *, int, int *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNDataDescriptor");
			fprintf(stderr, "wrapper_cudnnGetRNNDataDescriptor:%p\n", wrapper_cudnnGetRNNDataDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNDataDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNDataDescriptor(rnnDataDesc, dataType, layout, maxSeqLength, batchSize, vectorSize, arrayLengthRequested, seqLengthArray, paddingFill);
		return retval;
	}
}

