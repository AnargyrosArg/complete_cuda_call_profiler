#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamIsCapturing)(CUstream, CUstreamCaptureStatus *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamIsCapturing(CUstream hStream, CUstreamCaptureStatus *captureStatus) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamIsCapturing():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamIsCapturing)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamIsCapturing = (CUresult (*)(CUstream, CUstreamCaptureStatus *)) __libc_dlsym(libcuda_handle, "cuStreamIsCapturing");
			fprintf(stderr, "cuStreamIsCapturing:%p\n", original_cuStreamIsCapturing);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamIsCapturing():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamIsCapturing(hStream, captureStatus);
		return retval;
	}
}

