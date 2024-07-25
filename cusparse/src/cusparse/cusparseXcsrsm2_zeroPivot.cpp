#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsrsm2_zeroPivot)(cusparseHandle_t, csrsm2Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsrsm2_zeroPivot(cusparseHandle_t handle, csrsm2Info_t info, int *position) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsrsm2_zeroPivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsrsm2_zeroPivot = (cusparseStatus_t (*)(cusparseHandle_t, csrsm2Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsrsm2_zeroPivot");
			fprintf(stderr, "wrapper_cusparseXcsrsm2_zeroPivot:%p\n", wrapper_cusparseXcsrsm2_zeroPivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsrsm2_zeroPivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsrsm2_zeroPivot(handle, info, position);
		return retval;
	}
}