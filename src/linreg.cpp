// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
arma::mat linmodEstCpp1(arma::mat x,arma::vec y) {
  arma::vec coef = (x.t() * x).i() * x.t() * y;
  return(coef);
}

// [[Rcpp::export]]
List linmodEstCpp2(arma::mat x,arma::vec y) {

  arma::vec coef = (x.t() * x).i() * x.t() * y;
  int df = x.n_rows - x.n_cols;
  double sigma2 = sum(pow(y - x * coef, 2)) / df;
  arma::mat vcov = sigma2 * (x.t() * x).i();

  List out;
  out["coef"] = coef;
  out["vcov"] = vcov;
  out["sigma"] = pow(sigma2, 0.5);
  out["df"] = df;

  return(out);
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically
// run after the compilation.
//

/*** R
data(cats, package = "MASS")
Linreg::linmodEst(cbind(1, cats$Bwt), cats$Hwt)
linmodEstCpp1(cbind(1, cats$Bwt), cats$Hwt)
linmodEstCpp2(cbind(1, cats$Bwt), cats$Hwt)
*/
