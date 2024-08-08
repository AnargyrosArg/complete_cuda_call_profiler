#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuUserObjectCreate)(CUuserObject *, void *, CUhostFn, unsigned int, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuUserObjectCreate(CUuserObject *object_out, void *ptr, CUhostFn destroy, unsigned int initialRefcount, unsigned int flags) {
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
				fprintf(stderr, "dlsym error for fntion cuUserObjectCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuUserObjectCreate)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuUserObjectCreate = (CUresult (*)(CUuserObject *, void *, CUhostFn, unsigned int, unsigned int)) __libc_dlsym(libcuda_handle, "cuUserObjectCreate");
			fprintf(stderr, "cuUserObjectCreate:%p\n", original_cuUserObjectCreate);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuUserObjectCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuUserObjectCreate(object_out, ptr, destroy, initialRefcount, flags);
		return retval;
	}
}

