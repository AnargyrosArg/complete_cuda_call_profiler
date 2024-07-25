
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamGetCaptureInfo_v2)(cudaStream_t, enum cudaStreamCaptureStatus *, unsigned long long *, cudaGraph_t *, const cudaGraphNode_t **, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamGetCaptureInfo_v2(cudaStream_t stream, enum cudaStreamCaptureStatus *captureStatus_out, unsigned long long *id_out, cudaGraph_t *graph_out, const cudaGraphNode_t **dependencies_out, size_t *numDependencies_out) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamGetCaptureInfo_v2)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamGetCaptureInfo_v2 = (cudaError_t (*)(cudaStream_t, enum cudaStreamCaptureStatus *, unsigned long long *, cudaGraph_t *, const cudaGraphNode_t **, size_t *)) dlsym(libcudart_handle, "cudaStreamGetCaptureInfo_v2");
			fprintf(stderr, "cudaStreamGetCaptureInfo_v2:%p\n", wrapper_cudaStreamGetCaptureInfo_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamGetCaptureInfo_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamGetCaptureInfo_v2(stream, captureStatus_out, id_out, graph_out, dependencies_out, numDependencies_out);
		return retval;
	}
}

