/***********************************************************************/
//  Evolve Me A Cluster of StarS (EMACSS)                              //
//                                                                     //
//  By: Poul Alexander (University of Cambridge)                       //
//      Mark Gieles (University of Cambridge, University of Surrey)    //
//      Henny Lamers (University of Amsterdam)                         //
//      Holger Baumgardt (Univesity of Brisbane)                       //
//                                                                     //
//  EMACSS is a numerical integrator that solves for the differential  //
//  equations:                                                         //
//								       //
//  dE/dr = e(N,r,p) = -epsilon/t_rh				       //
//                                                                     //
//  dN/dt = f(N,r,p) = - xi*N/t_rh                                     // 
//                                                                     //
//  d<m>/dt = g(N,r,<m>,p) = - gamma*<m>/t_rh                          // 
//                                                                     //
//  dr/dt = h(N,r,p) = mu * r/t_rh                                     //
//                                                                     // 
//  d kappa/dt = i(kappa) = lambda * kappa/t_rh                        //
//                                                                     // 
//  where                                                              // 
//                                                                     // 
//  epsilon = f(N,r,rt,t)                                              //
//  xi = f(N,r,rt)                                                     //
//  mu = f(N,r,rt)                                                     //
//  gamma = f(N,r,rt,mm,t)                                             //
//  lambda = f(kappa,t)                                                //
//  p is an array of parameters/variables, which define the properties //
//  of star clusters at any given time in the life-cycle               //
//                                                                     //
// Equations referenced AG2012 refer to Alexander & Gieles 2012        //
// Equations referenced GALB2013 refer to Gieles et al. 2013           //
// Equations referenced AGLB2014 refer to Alexander et al. 2014        //
/***********************************************************************/

#include "emacss.h"

int main(int argc, char* argv[]){

  node cluster;
  stellar_evo se_module;
  dynamics dynamics_module;
  cluster.input(argc,argv);
  
  se_module.load(&cluster,&dynamics_module);
  dynamics_module.load(&cluster,&se_module);

  cluster.initialise(se_module,dynamics_module);
  //Creates initial conditions and t=0 output.
  
  cluster.load(&dynamics_module,&se_module);
  cluster.output(se_module,dynamics_module); 

  while (cluster.N > 100 && cluster.time < cluster.out_time){
    cluster.evolve(se_module,dynamics_module);	
    cluster.output(se_module,dynamics_module);
  }	      
  return 0;
}

