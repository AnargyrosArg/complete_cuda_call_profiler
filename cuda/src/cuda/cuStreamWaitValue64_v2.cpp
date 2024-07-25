#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamWaitValue64_v2)(CUstream, CUdeviceptr, cuuint64_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamWaitValue64_v2(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamWaitValue64_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamWaitValue64_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamWaitValue64_v2 = (CUresult (*)(CUstream, CUdeviceptr, cuuint64_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuStreamWaitValue64_v2");
			fprintf(stderr, "cuStreamWaitValue64_v2:%p\n", original_cuStreamWaitValue64_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamWaitValue64_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamWaitValue64_v2(stream, addr, value, flags);
		return retval;
	}
}

