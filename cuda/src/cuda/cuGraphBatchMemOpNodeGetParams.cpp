#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphBatchMemOpNodeGetParams)(CUgraphNode, CUDA_BATCH_MEM_OP_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphBatchMemOpNodeGetParams(CUgraphNode hNode, CUDA_BATCH_MEM_OP_NODE_PARAMS *nodeParams_out) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphBatchMemOpNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphBatchMemOpNodeGetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphBatchMemOpNodeGetParams = (CUresult (*)(CUgraphNode, CUDA_BATCH_MEM_OP_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphBatchMemOpNodeGetParams");
			fprintf(stderr, "cuGraphBatchMemOpNodeGetParams:%p\n", original_cuGraphBatchMemOpNodeGetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphBatchMemOpNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphBatchMemOpNodeGetParams(hNode, nodeParams_out);
		return retval;
	}
}

