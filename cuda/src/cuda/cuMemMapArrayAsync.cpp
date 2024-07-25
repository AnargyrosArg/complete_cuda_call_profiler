#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemMapArrayAsync)(CUarrayMapInfo *, unsigned int, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemMapArrayAsync(CUarrayMapInfo *mapInfoList, unsigned int count, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemMapArrayAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemMapArrayAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemMapArrayAsync = (CUresult (*)(CUarrayMapInfo *, unsigned int, CUstream)) __libc_dlsym(libcuda_handle, "cuMemMapArrayAsync");
			fprintf(stderr, "cuMemMapArrayAsync:%p\n", original_cuMemMapArrayAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemMapArrayAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemMapArrayAsync(mapInfoList, count, hStream);
		return retval;
	}
}

