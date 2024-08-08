#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnMatGetStridedBatch)(cusparseDnMatDescr_t, int *, int64_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnMatGetStridedBatch(cusparseDnMatDescr_t dnMatDescr, int *batchCount, int64_t *batchStride) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnMatGetStridedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnMatGetStridedBatch = (cusparseStatus_t (*)(cusparseDnMatDescr_t, int *, int64_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnMatGetStridedBatch");
			fprintf(stderr, "wrapper_cusparseDnMatGetStridedBatch:%p\n", wrapper_cusparseDnMatGetStridedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnMatGetStridedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnMatGetStridedBatch(dnMatDescr, batchCount, batchStride);
		return retval;
	}
}