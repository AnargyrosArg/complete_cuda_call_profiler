#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgesvd(cusolverDnHandle_t handle, signed char jobu, signed char jobvt, int m, int n, cuComplex *A, int lda, float *S, cuComplex *U, int ldu, cuComplex *VT, int ldvt, cuComplex *work, int lwork, float *rwork, int *info)
{
	cusolverStatus_t retval = cusolverDnCgesvd(handle, jobu, jobvt, m, n, A, lda, S, U, ldu, VT, ldvt, work, lwork, rwork, info);
	return retval;
}