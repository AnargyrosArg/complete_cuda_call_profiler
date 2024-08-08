#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMatGetSize)(cusparseSpMatDescr_t, int64_t *, int64_t *, int64_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMatGetSize(cusparseSpMatDescr_t spMatDescr, int64_t *rows, int64_t *cols, int64_t *nnz) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMatGetSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMatGetSize = (cusparseStatus_t (*)(cusparseSpMatDescr_t, int64_t *, int64_t *, int64_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMatGetSize");
			fprintf(stderr, "wrapper_cusparseSpMatGetSize:%p\n", wrapper_cusparseSpMatGetSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMatGetSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMatGetSize(spMatDescr, rows, cols, nnz);
		return retval;
	}
}