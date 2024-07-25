#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMatSetStridedBatch)(cusparseSpMatDescr_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMatSetStridedBatch(cusparseSpMatDescr_t spMatDescr, int batchCount) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMatSetStridedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMatSetStridedBatch = (cusparseStatus_t (*)(cusparseSpMatDescr_t, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMatSetStridedBatch");
			fprintf(stderr, "wrapper_cusparseSpMatSetStridedBatch:%p\n", wrapper_cusparseSpMatSetStridedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMatSetStridedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMatSetStridedBatch(spMatDescr, batchCount);
		return retval;
	}
}