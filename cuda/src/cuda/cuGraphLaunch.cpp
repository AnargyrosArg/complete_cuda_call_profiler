#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphLaunch)(CUgraphExec, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphLaunch(CUgraphExec hGraphExec, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphLaunch():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphLaunch)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphLaunch = (CUresult (*)(CUgraphExec, CUstream)) __libc_dlsym(libcuda_handle, "cuGraphLaunch");
			fprintf(stderr, "cuGraphLaunch:%p\n", original_cuGraphLaunch);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphLaunch():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphLaunch(hGraphExec, hStream);
		return retval;
	}
}

