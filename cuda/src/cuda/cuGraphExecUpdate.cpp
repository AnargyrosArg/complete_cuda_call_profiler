#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExecUpdate)(CUgraphExec, CUgraph, CUgraphNode *, CUgraphExecUpdateResult *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExecUpdate(CUgraphExec hGraphExec, CUgraph hGraph, CUgraphNode *hErrorNode_out, CUgraphExecUpdateResult *updateResult_out) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecUpdate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExecUpdate)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExecUpdate = (CUresult (*)(CUgraphExec, CUgraph, CUgraphNode *, CUgraphExecUpdateResult *)) __libc_dlsym(libcuda_handle, "cuGraphExecUpdate");
			fprintf(stderr, "cuGraphExecUpdate:%p\n", original_cuGraphExecUpdate);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecUpdate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExecUpdate(hGraphExec, hGraph, hErrorNode_out, updateResult_out);
		return retval;
	}
}

