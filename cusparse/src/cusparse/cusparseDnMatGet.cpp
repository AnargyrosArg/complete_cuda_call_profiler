#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnMatGet)(cusparseDnMatDescr_t, int64_t *, int64_t *, int64_t *, void **, cudaDataType *, cusparseOrder_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnMatGet(cusparseDnMatDescr_t dnMatDescr, int64_t *rows, int64_t *cols, int64_t *ld, void **values, cudaDataType *type, cusparseOrder_t *order) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnMatGet)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnMatGet = (cusparseStatus_t (*)(cusparseDnMatDescr_t, int64_t *, int64_t *, int64_t *, void **, cudaDataType *, cusparseOrder_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnMatGet");
			fprintf(stderr, "wrapper_cusparseDnMatGet:%p\n", wrapper_cusparseDnMatGet);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnMatGet():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnMatGet(dnMatDescr, rows, cols, ld, values, type, order);
		return retval;
	}
}