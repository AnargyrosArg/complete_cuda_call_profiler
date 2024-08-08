#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamWaitValue32)(CUstream, CUdeviceptr, cuuint32_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamWaitValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamWaitValue32():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamWaitValue32)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamWaitValue32 = (CUresult (*)(CUstream, CUdeviceptr, cuuint32_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuStreamWaitValue32");
			fprintf(stderr, "cuStreamWaitValue32:%p\n", original_cuStreamWaitValue32);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamWaitValue32():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamWaitValue32(stream, addr, value, flags);
		return retval;
	}
}

