#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetFilterNdDescriptor)(const cudnnFilterDescriptor_t, int, cudnnDataType_t *, cudnnTensorFormat_t *, int *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetFilterNdDescriptor(const cudnnFilterDescriptor_t filterDesc, int nbDimsRequested, cudnnDataType_t *dataType, cudnnTensorFormat_t *format, int *nbDims, int filterDimA[]) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetFilterNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetFilterNdDescriptor = (cudnnStatus_t (*)(const cudnnFilterDescriptor_t, int, cudnnDataType_t *, cudnnTensorFormat_t *, int *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetFilterNdDescriptor");
			fprintf(stderr, "wrapper_cudnnGetFilterNdDescriptor:%p\n", wrapper_cudnnGetFilterNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetFilterNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetFilterNdDescriptor(filterDesc, nbDimsRequested, dataType, format, nbDims, filterDimA);
		return retval;
	}
}

