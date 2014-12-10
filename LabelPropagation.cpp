# include "LabelPropagation.hpp"
# include "StringUtilities.hpp"
# include <sstream> 
# include<iostream>
# include <fstream>
# include <string>
# include <cstring>
# include <vector>
# include <stdlib.h>
# include <algorithm>
# include <iterator>
# include <cstdlib>
# include <cmath>
# include <iterator>
#include <ctime>  
# include <queue>
using namespace std;
StringUtilities su;
LabelPropagation::LabelPropagation()
{

}


void LabelPropagation::LoadWeightMatrix()

{
fstream myweightfile(&weightFile[0]);

WeightMatrix = new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
    WeightMatrix[i] = new double[noExamples];
}
string str;
double dummy=0.0;
int nr=0;
while(getline(myweightfile,str)){
   double  *p;
   p= su.SplitString(str,dummy); 
   for ( int i = 0; i < noExamples; i++ ) {
        WeightMatrix[nr][i]=*(p+i);
   }
  nr++;
  delete p;

}
}

void	LabelPropagation::TransitionMatrixCal(){


TransitionMatrix = new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
    TransitionMatrix[i] = new double[noExamples];
}


double rowSum=0.0;
for (int r=0; r<noExamples; r++){
   for (int c=0; c<noExamples;c++) {
     rowSum=rowSum+WeightMatrix[r][c];
}
   for(int l=0;l<noExamples;l++) 
   TransitionMatrix[r][l]=WeightMatrix[r][l] / rowSum;
  rowSum=0.0;

}
}

void	LabelPropagation::DiagonalMatrixCal(){


DiagonalMatrix= new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
    DiagonalMatrix[i] = new double[noExamples];
}


for (int r=0;r<noExamples;r++)
  for(int c=0;c<noExamples;c++)
       DiagonalMatrix[r][c]=0.0;

double rowSum=0.0;
for (int r=0; r<noExamples; r++){
   for (int c=0; c<noExamples;c++) {
     rowSum=rowSum+WeightMatrix[r][c];
}
   DiagonalMatrix[r][r]=sqrt(1/rowSum);
   rowSum=0.0;

}

}

void	LabelPropagation::ADiagonalMatrixCal(){


ADiagonalMatrix= new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
   ADiagonalMatrix[i] = new double[noExamples];
}

float  mu_2=0.0;
mu_2=alp_2/(1-alp_2);

for (int r=0;r<noExamples;r++)
  for(int c=0;c<noExamples;c++)
       ADiagonalMatrix[r][c]=0.0;

double rowSum=0.0;
for (int r=0; r<noExamples; r++){
     
      if(r<noLExamples)
      rowSum=1+mu_2*(1/pow(DiagonalMatrix[r][r],2.0))+mu_2*e_2;
      else
      rowSum=mu_2*(1/pow(DiagonalMatrix[r][r],2.0))+mu_2*e_2;
      
      ADiagonalMatrix[r][r]=rowSum;
      rowSum=0.0;

}

}


void	LabelPropagation::NormLaplacianMatrixCal(){


NormLaplacianMatrix= new double* [noExamples];
for(int i = 0; i < noExamples; ++i) {
    NormLaplacianMatrix[i] = new double[noExamples];
}


for (int r=0;r<noExamples;r++)
  for(int c=0;c<noExamples;c++)
       NormLaplacianMatrix[r][c]=0.0;


for (int r=0; r<noExamples; r++){
   for (int c=0; c<noExamples;c++) {
   double temp=0.0;
      for(int c1=0;c1<noExamples;c1++){
  temp=temp+DiagonalMatrix[r][c1]*WeightMatrix[c1][c]; 
}
NormLaplacianMatrix[r][c]=temp;
}
}



for (int r=0; r<noExamples; r++){
   for (int c=0; c<noExamples;c++) {
   double temp=0.0;
      for(int c1=0;c1<noExamples;c1++){
// NormLaplacianMatrix[r][c]=DiagonalMatrix[r][c]-WeightMatrix[r][c];
  temp=temp+NormLaplacianMatrix[r][c1]*DiagonalMatrix[c1][c]; 
}
NormLaplacianMatrix[r][c]=temp;
}
}

}


void LabelPropagation::DisplayWeightMatrix()
{


cout<< "Displaying WeightMatrix"<< endl;

for(int i=0;i<noExamples;i++){

    for (int j=0;j<noExamples;j++){

          cout<< WeightMatrix[i][j]<<"\t";



 }
cout<< "\n";

}

}

void LabelPropagation::DisplayTransitionMatrix()
{


cout<< "Displaying TransitionMatrix"<< endl;

for(int i=0;i<noExamples;i++){

    for (int j=0;j<noExamples;j++){

          cout<< TransitionMatrix[i][j]<<"\t";



 }
cout<< "\n";

}

}

void LabelPropagation::DisplayNormLaplacianMatrix()
{


cout<< "Displaying NormLaplacianMatrix"<< endl;

for(int i=0;i<noExamples;i++){

    for (int j=0;j<noExamples;j++){

          cout<< NormLaplacianMatrix[i][j]<<"\t";



 }
cout<< "\n";

}

}

void LabelPropagation::PrepareYMatrix()
{

OrgYMatrix=new double[noExamples];
IpYMatrix=new double[noExamples];
ActYMatrix=new double[noExamples];
Y0Matrix=new double[noExamples];

fstream mylabelfile(&IplabelFile[0]);

string str;
int r=0;
while(getline(mylabelfile,str)){

char *x=&str[0];
OrgYMatrix[r]=atoi(x);
IpYMatrix[r]=atoi(x);
Y0Matrix[r]=atoi(x);
r++;

}

}


void LabelPropagation::RunAlgorithm(){


switch(algoChoice)
{
case 1: LPAlgorithm1();
	break;
case 2: LPAlgorithm2();
	break;
case 3: LPAlgorithm3();
	break;
}
}

void LabelPropagation::LPAlgorithm1(){

cout<< "\n STARTED ALGO-1\n";
for (int i=0;i<noIterations;i++){
      MatrixProductComputation1();
      ClampInitialLabels1();
}
}

void LabelPropagation::LPAlgorithm2(){
cout<< "\n STARTED ALGO-2\n";
for (int i=0;i<noIterations;i++){
      MatrixProductComputation2();
      ClampInitialLabels2();
}
}


void LabelPropagation::LPAlgorithm3(){
cout<< "\n STARTED ALGO-3\n";
for (int i=0;i<noIterations;i++){
      MatrixProductComputation3();
      ClampInitialLabels3();
}

}

void    LabelPropagation::MatrixProductComputation3(){
double rsum=0.0;
for(int r=0;r<noExamples;r++)
{
      for (int c=0;c<noExamples;c++){
            
           rsum=rsum+NormLaplacianMatrix[r][c]*IpYMatrix[c];
     }
    ActYMatrix[r]=alpha*rsum + (1.0-alpha)*Y0Matrix[r];
    rsum=0.0;
}

}


void    LabelPropagation::MatrixProductComputation2(){


float  mu_2=0.0;
mu_2=alp_2/(1-alp_2);
double rsum=0.0;
for(int r=0;r<noExamples;r++)
{

     for (int c=0;c<noExamples;c++ ){
              
         rsum=rsum+WeightMatrix[r][c]*IpYMatrix[c];
     }
   
    ActYMatrix[r]=((mu_2*rsum)+Y0Matrix[r])/(ADiagonalMatrix[r][r]);
    rsum=0.0;

}

}
void    LabelPropagation::MatrixProductComputation1(){
double rsum=0.0;
for(int r=0;r<noExamples;r++)
{
      for (int c=0;c<noExamples;c++){
            
           rsum=rsum+TransitionMatrix[r][c]*IpYMatrix[c];
     }
    ActYMatrix[r]=rsum;
    rsum=0.0;
}

}


void    LabelPropagation::ClampInitialLabels1(){

/* Update IpY Matrix*/
for(int i=0;i<noExamples;i++)
IpYMatrix[i]=ActYMatrix[i];

/* Clamping Intial Labeled Data*/ 
for(int i=0;i<noLExamples;i++){
IpYMatrix[i]=Y0Matrix[i];
}


/*
cout<< "AFTER ITERATION IP Y MATRIX"<<endl;
for(int i=0;i<noExamples;i++)
cout<<IpYMatrix[i]<<endl;
*/


}

void    LabelPropagation::ClampInitialLabels2(){

for(int i=0;i<noExamples;i++){
IpYMatrix[i]=ActYMatrix[i];
}

}

void    LabelPropagation::ClampInitialLabels3(){
 
for(int i=0;i<noExamples;i++){
IpYMatrix[i]=ActYMatrix[i];
}

}


void    LabelPropagation::DisplayActYMatrix(){
 
for (int i=0;i<noExamples;i++)
  cout<< ActYMatrix[i]<<endl;

}


void LabelPropagation::DisplayOrgYMatrix()
{

cout<< "DISPLAYING Y MATRIX"<< endl;
for (int i=0; i<noExamples;i++)
cout<< OrgYMatrix[i]<<endl;


}



void    LabelPropagation::WriteOutPut(){


ofstream filafile;
filafile.open(&OplabelFile[0]);
for (int i=0; i<noExamples;i++){

if (ActYMatrix[i]>0)
filafile<<1<<"\n";
else
filafile<<-1<<"\n";

}

cout<< " Wrote the output to file"<<endl;

}
 
