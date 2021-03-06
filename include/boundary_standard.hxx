/// Some standard boundary conditions

#ifndef __BNDRY_STD_H__
#define __BNDRY_STD_H__

#include "boundary_op.hxx"
#include "bout_types.hxx"
#include <field_factory.hxx>

/// Dirichlet (set to zero) boundary condition
class BoundaryDirichlet : public BoundaryOp {
 public:
  BoundaryDirichlet() : val(0.) {}
  BoundaryDirichlet(const BoutReal setval): val(setval) {}
  BoundaryDirichlet(BoundaryRegion *region, BoutReal setval=0.):BoundaryOp(region),val(setval) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  BoutReal val;
};

/// Dirichlet boundary condition set half way between guard cell and grid cell at 2nd order accuracy
class BoundaryDirichlet_2ndOrder : public BoundaryOp {
 public:
  BoundaryDirichlet_2ndOrder() : val(0.) {}
  BoundaryDirichlet_2ndOrder(const BoutReal setval): val(setval) {}
  BoundaryDirichlet_2ndOrder(BoundaryRegion *region, BoutReal setval=0.):BoundaryOp(region),val(setval) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  BoutReal val;
};
//JMAD

class BndDirichlet_O2 : public BoundaryOp {
 public:
  BndDirichlet_O2();
  BndDirichlet_O2(BoundaryRegion *region, FieldGenerator *g);
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field2D &f,BoutReal t);
  void apply(Field3D &f);
  void apply(Field3D &f,BoutReal t);

  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  FieldGenerator* gen; // Generator
};

BoutReal default_func(BoutReal t, int x, int y, int z);
// END JMAD

/// Dirichlet boundary condition set half way between guard cell and grid cell at 4th order accuracy
class BoundaryDirichlet_4thOrder : public BoundaryOp {
 public:
  BoundaryDirichlet_4thOrder() : val(0.) {}
  BoundaryDirichlet_4thOrder(const BoutReal setval): val(setval) {}
  BoundaryDirichlet_4thOrder(BoundaryRegion *region, BoutReal setval=0.):BoundaryOp(region),val(setval) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  BoutReal val;
};

/// Neumann (zero-gradient) boundary condition
class BoundaryNeumann : public BoundaryOp {
 public:
  BoundaryNeumann(): val(0.) {}
  BoundaryNeumann(const BoutReal setval): val(setval) {}
  BoundaryNeumann(BoundaryRegion *region, BoutReal setval=0.):BoundaryOp(region),val(setval) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
 private:
  BoutReal val;
};

/// Neumann (zero-gradient) boundary condition, using 2nd order on boundary
class BoundaryNeumann2 : public BoundaryOp {
 public:
  BoundaryNeumann2() {}
  BoundaryNeumann2(BoundaryRegion *region):BoundaryOp(region) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
};

/// Neumann boundary condition set half way between guard cell and grid cell at 2nd order accuracy
class BoundaryNeumann_2ndOrder : public BoundaryOp {
 public:
  BoundaryNeumann_2ndOrder() : val(0.) {}
  BoundaryNeumann_2ndOrder(const BoutReal setval): val(setval) {}
  BoundaryNeumann_2ndOrder(BoundaryRegion *region, BoutReal setval=0.):BoundaryOp(region),val(setval) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  BoutReal val;
};

//JMAD
class BndNeumann_O2 : public BoundaryOp {
 public:
  BndNeumann_O2() : bndfunc(NULL), gen(NULL) {}
  BndNeumann_O2(BoundaryRegion *region, FieldGenerator*g):BoundaryOp(region), bndfunc(NULL), gen(g) {}
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field2D &f, BoutReal t);
  void apply(Field3D &f);
  void apply(Field3D &f,BoutReal t);

  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  FuncPtr bndfunc;
  FieldGenerator *gen;
};

/// Neumann boundary condition set half way between guard cell and grid cell at 4th order accuracy
class BoundaryNeumann_4thOrder : public BoundaryOp {
 public:
  BoundaryNeumann_4thOrder() : val(0.) {}
  BoundaryNeumann_4thOrder(const BoutReal setval): val(setval) {}
  BoundaryNeumann_4thOrder(BoundaryRegion *region, BoutReal setval=0.):BoundaryOp(region),val(setval) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  BoutReal val;
};

/// NeumannPar (zero-gradient) boundary condition on
/// the variable / sqrt(g_22)
class BoundaryNeumannPar : public BoundaryOp {
 public:
  BoundaryNeumannPar() {}
  BoundaryNeumannPar(BoundaryRegion *region):BoundaryOp(region) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
};

/// Robin (mix of Dirichlet and Neumann)
class BoundaryRobin : public BoundaryOp {
 public:
  BoundaryRobin() : aval(0.), bval(0.), gval(0.) {}
  BoundaryRobin(BoundaryRegion *region, BoutReal a, BoutReal b, BoutReal g):BoundaryOp(region), aval(a), bval(b), gval(g) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
private:
  BoutReal aval, bval, gval;
};

/// Constant gradient (zero second derivative)
class BoundaryConstGradient : public BoundaryOp {
 public:
  BoundaryConstGradient() {}
  BoundaryConstGradient(BoundaryRegion *region):BoundaryOp(region) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
};

/// Zero Laplacian, decaying solution
class BoundaryZeroLaplace : public BoundaryOp {
 public:
  BoundaryZeroLaplace() {}
  BoundaryZeroLaplace(BoundaryRegion *region):BoundaryOp(region) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
};

/// Zero Laplacian
class BoundaryZeroLaplace2 : public BoundaryOp {
 public:
  BoundaryZeroLaplace2() {}
  BoundaryZeroLaplace2(BoundaryRegion *region):BoundaryOp(region) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
};

/// Constant Laplacian, decaying solution
class BoundaryConstLaplace : public BoundaryOp {
 public:
  BoundaryConstLaplace() {}
  BoundaryConstLaplace(BoundaryRegion *region):BoundaryOp(region) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
};

/// Vector boundary condition Div(B) = 0, Curl(B) = 0
class BoundaryDivCurl : public BoundaryOp {
 public:
  BoundaryDivCurl() {}
  BoundaryDivCurl(BoundaryRegion *region):BoundaryOp(region) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f) { bout_error("ERROR: DivCurl boundary only for vectors"); }
  void apply(Field3D &f) { bout_error("ERROR: DivCurl boundary only for vectors"); }
  void apply(Vector2D &f);
  void apply(Vector3D &f);
};

/// Free boundary condition (evolve the field in the guard cells, using non-centred derivatives to calculate the ddt)
class BoundaryFree : public BoundaryOp {
 public:
  BoundaryFree() : val(0.) {apply_to_ddt = true;}
  BoundaryFree(const BoutReal setval): val(setval) {}
  BoundaryFree(BoundaryRegion *region, BoutReal setval=0.):BoundaryOp(region),val(setval) { }
  BoundaryOp* clone(BoundaryRegion *region, const list<string> &args);
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  BoutReal val;
};

/////////////////////////////////////////////////////////

/// Convert a boundary condition to a relaxing one
class BoundaryRelax : public BoundaryModifier {
 public:
  BoundaryRelax() : r(10.) {apply_to_ddt = true;}  // Set default rate
  BoundaryRelax(BoundaryOp *operation, BoutReal rate) : BoundaryModifier(operation) {r = fabs(rate); apply_to_ddt = true;}
  BoundaryOp* cloneMod(BoundaryOp *op, const list<string> &args);
  
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
 private:
  BoutReal r;
};

/// Apply boundary condition in shifted coordinates
class BoundaryShifted : public BoundaryModifier {
public:
  BoundaryShifted() {}
  BoundaryShifted(BoundaryOp *operation) : BoundaryModifier(operation) {}
  BoundaryOp* cloneMod(BoundaryOp *op, const list<string> &args);
  
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
private:
  
};

/// Increase the width of a boundary
class BoundaryWidth : public BoundaryModifier {
public:
  BoundaryWidth() : width(2) {}
  BoundaryWidth(BoundaryOp *operation, int wid) : BoundaryModifier(operation), width(wid) {}
  BoundaryOp* cloneMod(BoundaryOp *op, const list<string> &args);
  
  void apply(Field2D &f);
  void apply(Field3D &f);
  
  void apply_ddt(Field2D &f);
  void apply_ddt(Field3D &f);
private:
  int width;
};

#endif // __BNDRY_STD_H__
