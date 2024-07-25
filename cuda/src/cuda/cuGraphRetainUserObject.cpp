#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphRetainUserObject)(CUgraph, CUuserObject, unsigned int, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphRetainUserObject(CUgraph graph, CUuserObject object, unsigned int count, unsigned int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphRetainUserObject():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphRetainUserObject)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphRetainUserObject = (CUresult (*)(CUgraph, CUuserObject, unsigned int, unsigned int)) __libc_dlsym(libcuda_handle, "cuGraphRetainUserObject");
			fprintf(stderr, "cuGraphRetainUserObject:%p\n", original_cuGraphRetainUserObject);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphRetainUserObject():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphRetainUserObject(graph, object, count, flags);
		return retval;
	}
}

