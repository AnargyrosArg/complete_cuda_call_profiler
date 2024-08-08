#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgtsvInterleavedBatch)(cusparseHandle_t, int, int, double *, double *, double *, double *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgtsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, double *dl, double *d, double *du, double *x, int batchCount, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgtsvInterleavedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgtsvInterleavedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, int, double *, double *, double *, double *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgtsvInterleavedBatch");
			fprintf(stderr, "wrapper_cusparseDgtsvInterleavedBatch:%p\n", wrapper_cusparseDgtsvInterleavedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgtsvInterleavedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgtsvInterleavedBatch(handle, algo, m, dl, d, du, x, batchCount, pBuffer);
		return retval;
	}
}