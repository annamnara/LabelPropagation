# include <string>
# include <iterator>
# include <string>
# include <cstdlib>
# include <ctime>
# include <vector>
# include "StringUtilities.hpp"
using namespace std;
 double *  StringUtilities::SplitString(const std::string& stringtosplit,double  dummy)
{
     
     
     vector<string> tokens;
     const  string& delimiters = " ";
     string::size_type lastPos = stringtosplit.find_first_not_of(delimiters, 0);
     string::size_type pos     = stringtosplit.find_first_of(delimiters, lastPos);
      while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(stringtosplit.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = stringtosplit.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = stringtosplit.find_first_of(delimiters, lastPos);
    }
      int wc=0;  
      double* words = NULL;   // Pointer to int, initialize to nothing.
     int n=tokens.size();           // Size needed for array
     words = new  double[n]; 
     for(std::vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
             string x=*it;
             char *c=&x[0];
             words[wc]=strtod(c,&c);
             wc++;
 } 


return words;
  
}

int* StringUtilities::ShuffleArray(int *arr,int n)
{

srand(time(0)); 
 for (int i=0; i<n; i++) {
            int r = rand() % n;  // generate a random position
            int temp = arr[i]; 
            arr[i] = arr[r]; 
            arr[r] = temp;
        }



return arr;
}
