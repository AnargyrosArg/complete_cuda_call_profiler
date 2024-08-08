#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgtsv2_nopivot_bufferSizeExt)(cusparseHandle_t, int, int, const cuComplex *, const cuComplex *, const cuComplex *, const cuComplex *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgtsv2_nopivot_bufferSizeExt(cusparseHandle_t handle, int m, int n, const cuComplex *dl, const cuComplex *d, const cuComplex *du, const cuComplex *B, int ldb, size_t *bufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgtsv2_nopivot_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgtsv2_nopivot_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuComplex *, const cuComplex *, const cuComplex *, const cuComplex *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgtsv2_nopivot_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseCgtsv2_nopivot_bufferSizeExt:%p\n", wrapper_cusparseCgtsv2_nopivot_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgtsv2_nopivot_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgtsv2_nopivot_bufferSizeExt(handle, m, n, dl, d, du, B, ldb, bufferSizeInBytes);
		return retval;
	}
}