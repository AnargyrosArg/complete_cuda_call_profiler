#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateDnMat)(cusparseDnMatDescr_t *, int64_t, int64_t, int64_t, void *, cudaDataType, cusparseOrder_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateDnMat(cusparseDnMatDescr_t *dnMatDescr, int64_t rows, int64_t cols, int64_t ld, void *values, cudaDataType valueType, cusparseOrder_t order) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateDnMat)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateDnMat = (cusparseStatus_t (*)(cusparseDnMatDescr_t *, int64_t, int64_t, int64_t, void *, cudaDataType, cusparseOrder_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateDnMat");
			fprintf(stderr, "wrapper_cusparseCreateDnMat:%p\n", wrapper_cusparseCreateDnMat);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateDnMat():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateDnMat(dnMatDescr, rows, cols, ld, values, valueType, order);
		return retval;
	}
}