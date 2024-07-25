#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphReleaseUserObject)(CUgraph, CUuserObject, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphReleaseUserObject(CUgraph graph, CUuserObject object, unsigned int count) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphReleaseUserObject():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphReleaseUserObject)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphReleaseUserObject = (CUresult (*)(CUgraph, CUuserObject, unsigned int)) __libc_dlsym(libcuda_handle, "cuGraphReleaseUserObject");
			fprintf(stderr, "cuGraphReleaseUserObject:%p\n", original_cuGraphReleaseUserObject);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphReleaseUserObject():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphReleaseUserObject(graph, object, count);
		return retval;
	}
}

