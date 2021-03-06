#include <math.h>
#include <Rmath.h>
#include <Rcpp.h>

using namespace Rcpp;
//#-------------------------------------------------------------------------#
//' Function that computes a mean value for each bin
//'
//' @param x NumericVector - vector of values of a bin
//' @param n intiger - number of bins
//' @keywords internal
// [[Rcpp::export]]
NumericVector binMean(NumericVector x,int n) {
  
  int sz = x.size() ;// get the length of the input vector
  NumericVector res(n);// create the output vector
  double w_size=double(sz)/double(n); // window size can be a double
  
  // if the bins equals the vector size ,set the window size to 1
  if(sz == n){
    w_size=1;
  }
  
  // if the bins number larger than vector size return zeros 
  if(sz < n){
    return res;
  }
  
  double prev=0; // index for start positions over vector
  int prev2 ;// integers for indices
  int end2  ;
  double end;
  for(int i = 0; i< n; i++) {
    end = prev + (w_size); //get the end index of the interval
    prev2 = ceil(prev); // get the integer index for slices over vector
    end2 = ceil(end);
    if(i == (n-1)){ // for the last bin
      end2 = sz;
    }
    prev = prev + w_size; // update the begining index of the slice
    res[i] = std::accumulate(&x[prev2], &x[end2], 0.0)/(&x[end2]-&x[prev2]); //calculate the mean value of the bin
  }
  
  return res;
}

double Median_c(NumericVector x){
  int dint = x.size();
  double res;
  if(dint%2 == 0){
    std::sort(x.begin(), x.end());
    res = (x[(dint/2)-1] + x[dint/2] ) / 2; 
  }else{
    std::nth_element(x.begin(), x.begin()+dint/2, x.end());
    res = x[dint/2];
  }
  return res;
}

//' Function that computes a median value for each bin
//'
//' @param x NumericVector - vector of values of a bin
//' @param n intiger - number of bins
//' @keywords internal
// [[Rcpp::export]]
NumericVector binMedian(NumericVector x, int n) {
  
  int sz = x.size() ;// get the length of the input vector
  NumericVector res(n);// create the output vector
  double w_size=double(sz)/double(n); // window size can be a double
  
  // if the bins equals the vector size ,set the window size to 1
  if(sz == n){
    w_size=1;
  }
  
  // if the bins number larger than vector size return zeros 
  if(sz < n){
    return res;
  }
  
  double prev=0; // index for start positions over vector
  int prev2 ;  // integers for indices
  int end2  ;
  double end;
  for(int i = 0; i < n; i++) {
    end = prev + (w_size); //get the end index of the interval
    prev2 = ceil(prev); // get the integer index for slices over vector
    end2 = ceil(end);
    if(i == (n-1)){ // for the last bin
      end2 = sz;
    }
    prev = prev + w_size; // update the begining index of the slice
    
    NumericVector vec(&x[prev2], &x[end2]);
    res[i] = Median_c(vec);
    
  }
  
  return res;
}

//' Function that computes a maximum value for each bin
//'
//' @param x NumericVector - vector of values of a bin
//' @param n intiger - number of bins
//' @keywords internal
// [[Rcpp::export]]
NumericVector binMax(NumericVector x,int n) {
  
  int sz = x.size() ;// get the length of the input vector
  NumericVector res(n);// create the output vector
  double w_size=double(sz)/double(n); // window size can be a double
  
  // if the bins equals the vector size ,set the window size to 1
  if(sz == n){
    w_size=1;
  }
  
  // if the bins number larger than vector size return zeros 
  if(sz < n){
    return res;
  }
  
  double prev=0; // index for start positions over vector
  int prev2 ;// integers for indices
  int end2 ;
  double end;
  for(int i = 0; i < n; i++) {
    end = prev + (w_size); //get the end index of the interval
    prev2 = ceil(prev); // get the integer index for slices over vector
    end2 = ceil(end);
    prev = prev + w_size; // update the begining index of the slice
    res[i] = *std::max_element(&x[prev2], &x[end2]); //calculate the max value in the bin
  }
  
  return res;
}

//' Function that computes a minimum value for each bin
//'
//' @param x NumericVector - vector of values of a bin
//' @param n intiger - number of bins
//' @keywords internal
// [[Rcpp::export]]
NumericVector binMin(NumericVector x,int n) {
  
  int sz = x.size() ;// get the length of the input vector
  NumericVector res(n);// create the output vector
  double w_size=double(sz)/double(n); // window size can be a double
  // if the bins equals the vector size ,set the window size to 1
  if(sz == n){
    w_size=1;
  }
  
  // if the bins number larger than vector size return zeros 
  if(sz < n){
    return res;
  }
  
  double prev=0; // index for start positions over vector
  int prev2 ;// integers for indices
  int end2  ;
  double end;
  for(int i = 0; i < n; i++) {
    end = prev + (w_size); //get the end index of the interval
    prev2 = ceil(prev); // get the integer index for slices over vector
    end2 = ceil(end);
    if(i == (n-1)){ // for the last bin
      end2 = sz;
    }
    prev = prev + w_size; // update the begining index of the slice
    res[i] = *std::min_element(&x[prev2], &x[end2]); //calculate the max value in the bin
  }
  
  return res;
}

//' Function that computes a sum of values in a bin
//'
//' @param x NumericVector - vector of values of a bin
//' @param n intiger - number of bins
//' @keywords internal
// [[Rcpp::export]]
NumericVector binSum(NumericVector x,int n) {
  
  int sz = x.size() ;// get the length of the input vector
  NumericVector res(n);// create the output vector
  double w_size=double(sz)/double(n); // window size can be a double
  
  // if the bins equals the vector size ,set the window size to 1
  if(sz == n){
    w_size=1;
  }
  
  // if the bins number larger than vector size return zeros 
  if(sz < n){
    return res;
  }
  
  double prev=0; // index for start positions over vector
  int prev2 ;// integers for indices
  int end2  ;
  double end;
  for(int i = 0; i < n; i++) {
    end = prev + (w_size); //get the end index of the interval
    prev2 = ceil(prev); // get the integer index for slices over vector
    end2 = ceil(end);
    if(i == (n-1)){ // for the last bin
      end2 = sz;
    }
    prev = prev + w_size; // update the begining index of the slice
    res[i] = std::accumulate(&x[prev2], &x[end2], 0.0); //calculate the sum value of the bin
    
  }
  
  return res;
}

//#-------------------------------------------------------------------------#
//' Function creates a matrix storing data with desirable number of bins for each window 
//'
//' listSliceMean() function calls the binMean() function
//'  
//' @param xlist List of vectors storing values of a bin
//' @param n intiger - number of bins
//' @keywords internal
//' @export
// [[Rcpp::export]]
NumericMatrix  listSliceMean(List xlist,int n)   {
  int m = xlist.size();
  NumericMatrix res(m, n);
  NumericVector  subVec;
  for (int i = 0; i < m; i++) {
    subVec=binMean(xlist[i], n );
    for (int j = 0; j < n; j++) {
      res(i, j)=subVec[j];
    }
  }
  return res;
}

//' Function creates a matrix storing data with desirable number of bins for each window 
//'
//' listSliceMean() function calls the binMedian() function 
//' 
//' @param xlist List of vectors storing values of a bin
//' @param n intiger - number of bins
//' @keywords internal
//' @export
// [[Rcpp::export]]
NumericMatrix  listSliceMedian(List xlist,int n) {
  int m = xlist.size(); 
  NumericMatrix res(m, n);
  NumericVector  subVec;
  NumericVector tabx;
  for (int i = 0; i < m; i++) {
    subVec = binMedian(xlist[i], n); //gives vector of mean values
    res(i, _) = subVec;             //adds the vector to the matrix
  }
  return res;
}


//' Function creates a matrix storing data with desirable number of bins for each window 
//'
//' listSliceMax() function calls the binMax() function 
//' 
//' @param xlist List of vectors storing values of a bin
//' @param n intiger - number of bins
//' @keywords internal
//' @export
// [[Rcpp::export]]
NumericMatrix  listSliceMax(List xlist,int n) {
  int m = xlist.size(); 
  NumericMatrix res(m, n);
  NumericVector  subVec;
  NumericVector tabx;
  for (int i = 0; i < m; i++) {
    subVec = binMax(xlist[i], n); //gives vector of mean values
    res(i, _) = subVec;             //adds the vector to the matrix
  }
  return res;
}


//' Function creates a matrix storing data with desirable number of bins for each window 
//'
//' listSliceMin() function calls the binMin() function 
//' 
//' @param xlist List of vectors storing values of a bin
//' @param n intiger - number of bins
//' @keywords internal
//' @export
// [[Rcpp::export]]
NumericMatrix  listSliceMin(List xlist,int n) {
  int m = xlist.size(); 
  NumericMatrix res(m, n);
  NumericVector  subVec;
  NumericVector tabx;
  for (int i = 0; i < m; i++) {
    subVec = binMin(xlist[i], n); //gives vector of mean values
    res(i, _) = subVec;             //adds the vector to the matrix
  }
  return res;
}


//' Function creates a matrix storing data with desirable number of bins for each window 
//'
//' listSliceSum() function calls the binSum() function 
//' @param xlist List of vectors storing values of a bin
//' @param n intiger - number of bins
//' @keywords internal
//' @export
// [[Rcpp::export]]
NumericMatrix  listSliceSum(List xlist,int n) {
  int m = xlist.size(); 
  NumericMatrix res(m, n);
  NumericVector  subVec;
  NumericVector tabx;
  for (int i = 0; i < m; i++) {
    subVec = binSum(xlist[i], n); //gives vector of mean values
    res(i, _) = subVec;             //adds the vector to the matrix
  }
  return res;
}

