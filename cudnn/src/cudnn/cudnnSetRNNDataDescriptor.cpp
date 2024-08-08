#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetRNNDataDescriptor)(cudnnRNNDataDescriptor_t, cudnnDataType_t, cudnnRNNDataLayout_t, int, int, int, const int *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetRNNDataDescriptor(cudnnRNNDataDescriptor_t rnnDataDesc, cudnnDataType_t dataType, cudnnRNNDataLayout_t layout, int maxSeqLength, int batchSize, int vectorSize, const int seqLengthArray[], void *paddingFill){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetRNNDataDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetRNNDataDescriptor = (cudnnStatus_t (*)(cudnnRNNDataDescriptor_t, cudnnDataType_t, cudnnRNNDataLayout_t, int, int, int, const int *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetRNNDataDescriptor");
			fprintf(stderr, "wrapper_cudnnSetRNNDataDescriptor:%p\n", wrapper_cudnnSetRNNDataDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetRNNDataDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetRNNDataDescriptor(rnnDataDesc, dataType, layout, maxSeqLength, batchSize, vectorSize, seqLengthArray, paddingFill);
		return retval;
	}
}

