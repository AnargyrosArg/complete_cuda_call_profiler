#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamEndCapture)(CUstream, CUgraph *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamEndCapture(CUstream hStream, CUgraph *phGraph) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamEndCapture():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamEndCapture)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamEndCapture = (CUresult (*)(CUstream, CUgraph *)) __libc_dlsym(libcuda_handle, "cuStreamEndCapture");
			fprintf(stderr, "cuStreamEndCapture:%p\n", original_cuStreamEndCapture);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamEndCapture():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamEndCapture(hStream, phGraph);
		return retval;
	}
}

