/*!************************************************************************
 * 
 * @brief Base class for Physics Models
 * 
 * 
 *
 * Changelog:
 * 
 * 2013-08 Ben Dudson <benjamin.dudson@york.ac.uk>
 *    * Initial version
 * 
 **************************************************************************
 * Copyright 2013 B.D.Dudson
 *
 * Contact: Ben Dudson, bd512@york.ac.uk
 * 
 * This file is part of BOUT++.
 *
 * BOUT++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BOUT++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with BOUT++.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/

class PhysicsModel;

#ifndef __PHYSICS_MODEL_H__
#define __PHYSICS_MODEL_H__

#include <bout.hxx>
#include <options.hxx>
#include <msg_stack.hxx>
#include "solver.hxx"

/*!
  Base class for physics models
 */
class PhysicsModel {
public:
  typedef int (PhysicsModel::*rhsfunc)(BoutReal t);
  typedef int (PhysicsModel::*preconfunc)(BoutReal t, BoutReal gamma, BoutReal delta);
  typedef int (PhysicsModel::*jacobianfunc)(BoutReal t);
  
  PhysicsModel() : solver(0), userrhs(&PhysicsModel::rhs), userconv(0), userdiff(0), 
                   userprecon(0), userjacobian(0) {}
  ~PhysicsModel();
  
  int initialise(Solver *s, bool restarting) {
    solver = s;
    return init(restarting); // Call user code
  }
  
  int runRHS(BoutReal time);
  
  bool splitOperator();
  int runConvective(BoutReal time);
  int runDiffusive(BoutReal time);
  
  bool hasPrecon();
  int runPrecon(BoutReal t, BoutReal gamma, BoutReal delta);
  
  bool hasJacobian();
  int runJacobian(BoutReal t);

  int runOutputMonitor(BoutReal simtime, int iter, int NOUT) {return outputMonitor(simtime, iter, NOUT);}
  int runTimestepMonitor(BoutReal simtime, BoutReal dt) {return timestepMonitor(simtime, dt);}
protected:

  // These two functions implemented by user code to specify problem
  /*!
   * @brief This function is called once by the solver at the start of a simulation.
   * 
   * A valid PhysicsModel must implement this function
   * 
   * Variables should be read from the inputs, and the variables to 
   * be evolved should be specified.
   */
  virtual int init(bool restarting) = 0;
  
  /*!
   * @brief This function is called by the time integration solver
   * at least once per time step
   * 
   * Variables being evolved will be set by the solver
   * before the call, and this function must calculate
   * and set the time-derivatives.
   *
   * By default this function just returns an error,
   * which will stop the simulation.
   */
  virtual int rhs(BoutReal t) {return 1;} 

  // Implemented by user code to monitor solution
  virtual int outputMonitor(BoutReal simtime, int iter, int NOUT) {return 0;}
  virtual int timestepMonitor(BoutReal simtime, BoutReal dt) {return 0;}

  // Functions called by the user to set callback functions
  void setRHS(rhsfunc fset);
  void setSplitOperator(rhsfunc conv, rhsfunc diff);
  void setPrecon(preconfunc pset) {userprecon = pset;}
  void setJacobian(jacobianfunc jset) {userjacobian = jset;}

  Solver *solver;
  void bout_solve(Field2D &var, const char *name);
  void bout_solve(Field3D &var, const char *name);
  void bout_solve(Vector2D &var, const char *name);
  void bout_solve(Vector3D &var, const char *name);
  
  bool bout_constrain(Field3D &var, Field3D &F_var, const char *name);
private:
  rhsfunc      userrhs;
  rhsfunc      userconv, userdiff; // Split operator functions
  preconfunc   userprecon;
  jacobianfunc userjacobian;
};

// Macro to define a simple main() which creates
// the given model and runs it.
#define BOUTMAIN(ModelClass)                          \
  int main(int argc, char **argv) {                   \
    BoutInitialise(argc, argv);                       \
    try {                                             \
      ModelClass *model = new ModelClass();           \
      Solver *solver = Solver::create();              \
      solver->setModel(model);                        \
      solver->addMonitor(bout_monitor, Solver::BACK); \
      solver->outputVars(dump);                       \
      solver->solve();                                \
      delete model;                                   \
      delete solver;                                  \
    }catch (BoutException &e) {                       \
      output << "Error encountered\n";                \
      output << e.what() << endl;                     \
      MPI_Abort(BoutComm::get(), 1);                  \
    }                                                 \
    BoutFinalise();                                   \
    return 0;                                         \
  }


#endif // __PHYSICS_MODEL_H__

