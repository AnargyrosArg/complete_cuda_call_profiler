#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamGetCaptureInfo_v2)(CUstream, CUstreamCaptureStatus *, cuuint64_t *, CUgraph *, const CUgraphNode **, size_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamGetCaptureInfo_v2(CUstream hStream, CUstreamCaptureStatus *captureStatus_out, cuuint64_t *id_out, CUgraph *graph_out, const CUgraphNode **dependencies_out, size_t *numDependencies_out) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamGetCaptureInfo_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamGetCaptureInfo_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamGetCaptureInfo_v2 = (CUresult (*)(CUstream, CUstreamCaptureStatus *, cuuint64_t *, CUgraph *, const CUgraphNode **, size_t *)) __libc_dlsym(libcuda_handle, "cuStreamGetCaptureInfo_v2");
			fprintf(stderr, "cuStreamGetCaptureInfo_v2:%p\n", original_cuStreamGetCaptureInfo_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamGetCaptureInfo_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamGetCaptureInfo_v2(hStream, captureStatus_out, id_out, graph_out, dependencies_out, numDependencies_out);
		return retval;
	}
}

