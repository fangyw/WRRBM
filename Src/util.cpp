#include <cassert>
#include <cmath>
#include <cstring>
#include "util.h"
void biSampling(double *pProbs, double *pValues, int len)
{
	if (pProbs == NULL || pValues == NULL)
	{
		fprintf(stderr, "Error: sampling with null pointers\n");
		exit(0);
	}

	for (int i = 0; i < len; ++i)
		pValues[i] = uniform(0, 1.0) < pProbs[i] ? 1.0: 0.0;
}


void disVec(double *p, double thres, double upperBound, 
						int window, 	int dim, 	FILE *fp)
{
	fprintf(fp, "%d * %d\n", window, dim);
	for (int i = 0; i < window; ++i)
	{
		for (int d = 0; d < dim; ++d)
		{
			if (*p < thres)
				fprintf(fp, "---------- ");
			else if (*p > upperBound)
				fprintf(fp, "|||||||||| ");
			else
				fprintf(fp, "%-10.7f ", *p);
			++p;
		}
		fprintf(fp, "\n");
	}
}

void biSampling(double *pProbs, vector<double> &rValues, int len)
{
	if (pProbs == NULL)
	{
		fprintf(stderr, "Error: sampling with null pointers\n");
		exit(0);
	}
	
	rValues.resize(len);
	for (int i = 0; i < len; ++i)
		rValues[i] = uniform(0, 1.0) < pProbs[i] ? 1.0: 0.0;
}

void normalize(double *pVec, int len)
{
	double sum = 0;
	for (int i = 0; i < len; ++i)
		sum += pVec[i] * pVec[i];

	sum = sqrt(sum);
	for (int i = 0; i < len; ++i)
		pVec[i] /= sum;
}

double vecLen(double *pVec, int len)
{
	double sum = 0;
	for (int i = 0; i < len; ++i)
		sum += pVec[i] * pVec[i];

	return sqrt(sum);
}

double Dis(double *l, double *r, int len)
{
	double sum = 0;
	for (int i = 0; i < len; ++i)
		sum += (l[i] - r[i]) * (l[i] - r[i]);
	return sqrt(sum);
}


void vecInc(double *p1, double *p2, int len)
{
	for (int i = 0; i < len; ++i)
		p1[i] += p2[i];
}

double *scalarMult(double *pV, int len, double scalar)
{
	assert(pV != NULL);
	assert(len > 0);
	for (int i = 0; i < len; ++i)
		pV[i] *= scalar;

	return pV;
}

double dotProduct(double *pV1, int len1,  double *pV2, int len2)
{
  if (len1 != len2)
  {
    fprintf(stderr, "Error: vector length inconsistent l1 %d vs l2 %d\n", 
            len1, len2);
    exit(0);
  }

  if (pV1 == NULL || pV2 == NULL)
  {
    fprintf(stderr, "Error: dot_prod with null pointer\n");
    exit(0);
  }

  if (len1 <= 0 || len2 <=0)
  {
    fprintf(stderr, "Error: dot product with zero or negative length vector\n");
    exit(0);
  }

  double sum = 0.0;
  for (int i = 0; i < len1; ++i)
    sum += pV1[i] * pV2[i];

  return sum;
}

void disVec(double *pVec, int len, FILE *fp)
{
	for (int i = 0; i < len; ++i)
	{
		fprintf(fp, "[%d:%-6.2e]  ", i, pVec[i]);
		if ((i + 1) % 10 == 0)
			fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
}

void disSparseVec(double *pVec, int len, FILE *fp)
{
	for (int i = 0; i < len; ++i)
		if (pVec[i] > 1.0e-3 || pVec[i] < -1.0e-3)
			fprintf(fp, "[%d:%-5.3e]  ", i, pVec[i]);
	fprintf(fp, "\n");
}

void getCol(double **pMatrix, int rNum, int cNum, int cIdx, double *pRes)
{
  for (int rIdx = 0; rIdx < rNum; ++rIdx)
    pRes[rIdx] = pMatrix[rIdx][cIdx];
}

vector<char *> Split(char *pBuf, const char *pDelem)
{
	vector<char *> resVec;
	if (pBuf == NULL || pDelem == NULL)
		return resVec;

	char *p = pBuf;
	while (true)
	{
		while (*p && strchr(pDelem, *p) != NULL)
			*p ++ = 0;

		if (!*p)
			break;

//		fprintf(stderr, "before %lu, %s %d\n", resVec.size(), p,
//						(int*)p);
		resVec.push_back(p);
//		fprintf(stderr, "after  %lu, %s %d\n", resVec.size(), p,
//						(int*)p);
		while (*p && strchr(pDelem, *p) == NULL)
			p++;
	}

	return resVec;
}

//--------------------------------------------------------------------------------
vector<wchar_t *> Split(wchar_t *pBuf, const wchar_t *pDelem)
{
	vector<wchar_t *> resVec;
	if (pBuf == NULL || pDelem == NULL)
		return resVec;

	wchar_t *p = pBuf;
	while (true)
	{
		while (*p && wcschr(pDelem, *p) != NULL)
			*p ++ = 0;

		if (!*p)
			break;

		resVec.push_back(p);
		while (*p && wcschr(pDelem, *p) == NULL)
			p++;
	}

	return resVec;
}

