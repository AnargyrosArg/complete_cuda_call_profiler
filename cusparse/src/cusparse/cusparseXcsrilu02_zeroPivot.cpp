#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsrilu02_zeroPivot)(cusparseHandle_t, csrilu02Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsrilu02_zeroPivot(cusparseHandle_t handle, csrilu02Info_t info, int *position) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsrilu02_zeroPivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsrilu02_zeroPivot = (cusparseStatus_t (*)(cusparseHandle_t, csrilu02Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsrilu02_zeroPivot");
			fprintf(stderr, "wrapper_cusparseXcsrilu02_zeroPivot:%p\n", wrapper_cusparseXcsrilu02_zeroPivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsrilu02_zeroPivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsrilu02_zeroPivot(handle, info, position);
		return retval;
	}
}