#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuEventRecordWithFlags)(CUevent, CUstream, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuEventRecordWithFlags(CUevent hEvent, CUstream hStream, unsigned int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuEventRecordWithFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuEventRecordWithFlags)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuEventRecordWithFlags = (CUresult (*)(CUevent, CUstream, unsigned int)) __libc_dlsym(libcuda_handle, "cuEventRecordWithFlags");
			fprintf(stderr, "cuEventRecordWithFlags:%p\n", original_cuEventRecordWithFlags);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuEventRecordWithFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuEventRecordWithFlags(hEvent, hStream, flags);
		return retval;
	}
}
