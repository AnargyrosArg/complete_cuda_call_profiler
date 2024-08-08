#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexObjectCreate)(CUtexObject *, const CUDA_RESOURCE_DESC *, const CUDA_TEXTURE_DESC *, const CUDA_RESOURCE_VIEW_DESC *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexObjectCreate(CUtexObject *pTexObject, const CUDA_RESOURCE_DESC *pResDesc, const CUDA_TEXTURE_DESC *pTexDesc, const CUDA_RESOURCE_VIEW_DESC *pResViewDesc) {
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
				fprintf(stderr, "dlsym error for fntion cuTexObjectCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexObjectCreate)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexObjectCreate = (CUresult (*)(CUtexObject *, const CUDA_RESOURCE_DESC *, const CUDA_TEXTURE_DESC *, const CUDA_RESOURCE_VIEW_DESC *)) __libc_dlsym(libcuda_handle, "cuTexObjectCreate");
			fprintf(stderr, "cuTexObjectCreate:%p\n", original_cuTexObjectCreate);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexObjectCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexObjectCreate(pTexObject, pResDesc, pTexDesc, pResViewDesc);
		return retval;
	}
}

