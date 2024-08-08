#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsrsv2_zeroPivot)(cusparseHandle_t, csrsv2Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsrsv2_zeroPivot(cusparseHandle_t handle, csrsv2Info_t info, int *position) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsrsv2_zeroPivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsrsv2_zeroPivot = (cusparseStatus_t (*)(cusparseHandle_t, csrsv2Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsrsv2_zeroPivot");
			fprintf(stderr, "wrapper_cusparseXcsrsv2_zeroPivot:%p\n", wrapper_cusparseXcsrsv2_zeroPivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsrsv2_zeroPivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsrsv2_zeroPivot(handle, info, position);
		return retval;
	}
}