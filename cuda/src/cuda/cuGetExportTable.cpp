#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGetExportTable)(const void **, const CUuuid *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGetExportTable(const void **ppExportTable, const CUuuid *pExportTableId) {
		char* __dlerror;
		char uuid[38];
		sprintf(uuid,"%p %p",*pExportTableId,*(pExportTableId+8));
		fprintf(stderr, "%s() -> UUID:%s\n", __func__,uuid);

		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGetExportTable():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGetExportTable)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGetExportTable = (CUresult (*)(const void **, const CUuuid *)) __libc_dlsym(libcuda_handle, "cuGetExportTable");
			fprintf(stderr, "cuGetExportTable:%p\n", original_cuGetExportTable);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGetExportTable():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGetExportTable(ppExportTable, pExportTableId);
		return retval;
	}
}

