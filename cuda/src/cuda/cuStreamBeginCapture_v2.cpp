#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamBeginCapture_v2)(CUstream, CUstreamCaptureMode);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamBeginCapture_v2(CUstream hStream, CUstreamCaptureMode mode) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamBeginCapture_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamBeginCapture_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamBeginCapture_v2 = (CUresult (*)(CUstream, CUstreamCaptureMode)) __libc_dlsym(libcuda_handle, "cuStreamBeginCapture_v2");
			fprintf(stderr, "cuStreamBeginCapture_v2:%p\n", original_cuStreamBeginCapture_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamBeginCapture_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamBeginCapture_v2(hStream, mode);
		return retval;
	}
}

