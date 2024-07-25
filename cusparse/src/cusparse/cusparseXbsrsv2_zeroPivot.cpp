#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXbsrsv2_zeroPivot)(cusparseHandle_t, bsrsv2Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXbsrsv2_zeroPivot(cusparseHandle_t handle, bsrsv2Info_t info, int *position) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXbsrsv2_zeroPivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXbsrsv2_zeroPivot = (cusparseStatus_t (*)(cusparseHandle_t, bsrsv2Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXbsrsv2_zeroPivot");
			fprintf(stderr, "wrapper_cusparseXbsrsv2_zeroPivot:%p\n", wrapper_cusparseXbsrsv2_zeroPivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXbsrsv2_zeroPivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXbsrsv2_zeroPivot(handle, info, position);
		return retval;
	}
}