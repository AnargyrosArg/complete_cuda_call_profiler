#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpVecGetIndexBase)(cusparseSpVecDescr_t, cusparseIndexBase_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpVecGetIndexBase(cusparseSpVecDescr_t spVecDescr, cusparseIndexBase_t *idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpVecGetIndexBase)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpVecGetIndexBase = (cusparseStatus_t (*)(cusparseSpVecDescr_t, cusparseIndexBase_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpVecGetIndexBase");
			fprintf(stderr, "wrapper_cusparseSpVecGetIndexBase:%p\n", wrapper_cusparseSpVecGetIndexBase);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpVecGetIndexBase():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpVecGetIndexBase(spVecDescr, idxBase);
		return retval;
	}
}