#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetAttnDescriptor)(cudnnAttnDescriptor_t, unsigned, int, double, cudnnDataType_t, cudnnDataType_t, cudnnMathType_t, cudnnDropoutDescriptor_t, cudnnDropoutDescriptor_t, int, int, int, int, int, int, int, int, int, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetAttnDescriptor(cudnnAttnDescriptor_t attnDesc, unsigned attnMode, int nHeads, double smScaler, cudnnDataType_t dataType, cudnnDataType_t computePrec, cudnnMathType_t mathType, cudnnDropoutDescriptor_t attnDropoutDesc, cudnnDropoutDescriptor_t postDropoutDesc, int qSize, int kSize, int vSize, int qProjSize, int kProjSize, int vProjSize, int oProjSize, int qoMaxSeqLength, int kvMaxSeqLength, int maxBatchSize, int maxBeamSize){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetAttnDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetAttnDescriptor = (cudnnStatus_t (*)(cudnnAttnDescriptor_t, unsigned, int, double, cudnnDataType_t, cudnnDataType_t, cudnnMathType_t, cudnnDropoutDescriptor_t, cudnnDropoutDescriptor_t, int, int, int, int, int, int, int, int, int, int, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetAttnDescriptor");
			fprintf(stderr, "wrapper_cudnnSetAttnDescriptor:%p\n", wrapper_cudnnSetAttnDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetAttnDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetAttnDescriptor(attnDesc, attnMode, nHeads, smScaler, dataType, computePrec, mathType, attnDropoutDesc, postDropoutDesc, qSize, kSize, vSize, qProjSize, kProjSize, vProjSize, oProjSize, qoMaxSeqLength, kvMaxSeqLength, maxBatchSize, maxBeamSize);
		return retval;
	}
}

