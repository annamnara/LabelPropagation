# include <sstream> 
# include<iostream>
# include <fstream>
# include <string>
# include <vector>
# include <stdlib.h>
# include <algorithm>
# include <iterator>
# include <cstdlib>
# include <math.h>
# include <iterator>
#include <ctime> 
#include <cstring> 
#include <stdio.h> 
# include "LabelPropagation.hpp"
using namespace std;
int main(int argc, char* argv[])
{


LabelPropagation  lp;

FILE* fp;
fp=fopen(argv[1],"r");
char  paramName[50];
char  paramType[50];
char  paramValue[50];
char  line[100];

while (fgets(line,500,fp) != NULL) {
if(line[0]!='#')
{

sscanf(line,"%s %s %s",paramName,paramType,paramValue);

if(strcmp(paramName,"weightFile")==0)
lp.weightFile=paramValue;

if(strcmp(paramName,"IplabelFile")==0)
lp.IplabelFile=paramValue;

if(strcmp(paramName,"OplabelFile")==0)
lp.OplabelFile=paramValue;

if(strcmp(paramName,"noExamples")==0)
lp.noExamples=atoi(paramValue);

if(strcmp(paramName,"noClasses")==0)
lp.noClasses=atoi(paramValue);

if(strcmp(paramName,"noLExamples")==0)
lp.noLExamples=atoi(paramValue);

if(strcmp(paramName,"algoChoice")==0)
lp.algoChoice=atoi(paramValue);

if(strcmp(paramName,"lbr")==0)
lp.lbr=atoi(paramValue);

if(strcmp(paramName,"noitr")==0)
lp.noIterations=atoi(paramValue);

if(strcmp(paramName,"alpha")==0)
lp.alpha=atof(paramValue);

if(strcmp(paramName,"alp_2")==0)
lp.alp_2=atof(paramValue);

if(strcmp(paramName,"e_2")==0)
lp.e_2=atof(paramValue);
}
 
}
cout<< "params are:-- "<< "No. of Exmaples "<<lp.noExamples<<" \t"<< " Weight filename: "<< lp.weightFile<<"\t"<< "Iterations: "<<lp.noIterations<< "\t"<<endl;
cout<< "params are:-- "<< "No. of LExmaples "<<lp.noLExamples<<" \t"<< "Algorthim: "<< lp.algoChoice<<"\t"<< "Iterations: "<<lp.noIterations<< "\t"<<endl;

/*   Graph Construction Process */
lp.LoadWeightMatrix();
//lp.DisplayWeightMatrix();

lp.TransitionMatrixCal();
//lp.DisplayTransitionMatrix();

lp.DiagonalMatrixCal();
lp.ADiagonalMatrixCal();
lp.NormLaplacianMatrixCal();
//lp.DisplayNormLaplacianMatrix();

/* ===================================== */

/* Lable File Preparation*/

lp.PrepareYMatrix();
//lp.DisplayOrgYMatrix();

/* ===================================== */

/* Algortihms -V1, V3 */

lp.RunAlgorithm();
lp.WriteOutPut();
lp.DisplayActYMatrix();


}

