#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCsrSetStridedBatch)(cusparseSpMatDescr_t, int, int64_t, int64_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCsrSetStridedBatch(cusparseSpMatDescr_t spMatDescr, int batchCount, int64_t offsetsBatchStride, int64_t columnsValuesBatchStride) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCsrSetStridedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCsrSetStridedBatch = (cusparseStatus_t (*)(cusparseSpMatDescr_t, int, int64_t, int64_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCsrSetStridedBatch");
			fprintf(stderr, "wrapper_cusparseCsrSetStridedBatch:%p\n", wrapper_cusparseCsrSetStridedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCsrSetStridedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCsrSetStridedBatch(spMatDescr, batchCount, offsetsBatchStride, columnsValuesBatchStride);
		return retval;
	}
}