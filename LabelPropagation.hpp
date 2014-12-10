# include <iostream>
# include <string>
using namespace std;
class  LabelPropagation
{

public:
double 	**WeightMatrix;
double 	**TransitionMatrix;
double	**DiagonalMatrix;
double	**ADiagonalMatrix;
double 	**NormLaplacianMatrix;
double	*OrgYMatrix;
double	*IpYMatrix;
double	*ActYMatrix;
double	*Y0Matrix;

int 	noExamples;
int 	noLExamples;
int 	noIterations;
int 	noClasses;
int 	algoChoice;
int 	lbr;
float  	alpha;
float  	alp_2;
float  	e_2;
string 	weightFile;
string  IplabelFile;
string  OplabelFile;
string 	methodChoice;
	LabelPropagation();
void 	LoadWeightMatrix();
void	TransitionMatrixCal();
void	DiagonalMatrixCal();
void	ADiagonalMatrixCal();
void	NormLaplacianMatrixCal();

void	DisplayWeightMatrix();
void	DisplayTransitionMatrix();
void	DisplayNormLaplacianMatrix();
void 	DisplayOrgYMatrix();

void 	PrepareYMatrix();
void	RunAlgorithm();
void	LPAlgorithm1();
void	LPAlgorithm2();
void	LPAlgorithm3();
void	MatrixProductComputation1();
void	MatrixProductComputation2();
void	MatrixProductComputation3();
void	ClampInitialLabels1();
void	ClampInitialLabels2();
void	ClampInitialLabels3();
void	DisplayActYMatrix();
void	WriteOutPut();

};

  
