#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpGEMM_destroyDescr)(cusparseSpGEMMDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpGEMM_destroyDescr(cusparseSpGEMMDescr_t descr) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpGEMM_destroyDescr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpGEMM_destroyDescr = (cusparseStatus_t (*)(cusparseSpGEMMDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpGEMM_destroyDescr");
			fprintf(stderr, "wrapper_cusparseSpGEMM_destroyDescr:%p\n", wrapper_cusparseSpGEMM_destroyDescr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpGEMM_destroyDescr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpGEMM_destroyDescr(descr);
		return retval;
	}
}