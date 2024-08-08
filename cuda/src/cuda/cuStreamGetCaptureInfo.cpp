#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamGetCaptureInfo)(CUstream, CUstreamCaptureStatus *, cuuint64_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamGetCaptureInfo(CUstream hStream, CUstreamCaptureStatus *captureStatus_out, cuuint64_t *id_out) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamGetCaptureInfo():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamGetCaptureInfo)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamGetCaptureInfo = (CUresult (*)(CUstream, CUstreamCaptureStatus *, cuuint64_t *)) __libc_dlsym(libcuda_handle, "cuStreamGetCaptureInfo");
			fprintf(stderr, "cuStreamGetCaptureInfo:%p\n", original_cuStreamGetCaptureInfo);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamGetCaptureInfo():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamGetCaptureInfo(hStream, captureStatus_out, id_out);
		return retval;
	}
}

