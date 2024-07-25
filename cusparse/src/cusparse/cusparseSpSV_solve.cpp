#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpSV_solve)(cusparseHandle_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnVecDescr_t, cusparseDnVecDescr_t, cudaDataType, cusparseSpSVAlg_t, cusparseSpSVDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpSV_solve(cusparseHandle_t handle, cusparseOperation_t opA, const void *alpha, cusparseSpMatDescr_t matA, cusparseDnVecDescr_t vecX, cusparseDnVecDescr_t vecY, cudaDataType computeType, cusparseSpSVAlg_t alg, cusparseSpSVDescr_t spsvDescr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpSV_solve)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpSV_solve = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnVecDescr_t, cusparseDnVecDescr_t, cudaDataType, cusparseSpSVAlg_t, cusparseSpSVDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpSV_solve");
			fprintf(stderr, "wrapper_cusparseSpSV_solve:%p\n", wrapper_cusparseSpSV_solve);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpSV_solve():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpSV_solve(handle, opA, alpha, matA, vecX, vecY, computeType, alg, spsvDescr);
		return retval;
	}
}