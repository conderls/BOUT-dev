#include <bout.hxx>

#include <invert_laplace.hxx>
#include <field_factory.hxx>
#include <bout/constants.hxx>

int main(int argc, char **argv) {
  BoutInitialise(argc, argv);
  
  ////// Set mesh spacing
  Options *meshoptions = Options::getRoot()->getSection("mesh");

  BoutReal Lx;
  meshoptions->get("Lx",Lx,1.0);

  /*this assumes equidistant grid*/
  int nguard = mesh->xstart;
  mesh->dx = Lx/(mesh->GlobalNx - 2*nguard);
  mesh->dz = TWOPI*Lx/(mesh->ngz-1);
  mesh->zlength = TWOPI*Lx;
  /////

  // Create a Laplacian inversion solver
  Laplacian *lap = Laplacian::create();
  
  FieldFactory fact(mesh);

  FieldGenerator *gen = fact.parse("input");
  output << "GEN = " << gen->str() << endl;

  Field3D input = fact.create3D("input");
  
  Field3D result = lap->solve(input);
  
  Field3D solution = fact.create3D("solution");

  Field3D error = result - solution;

  SAVE_ONCE4(input, result, solution, error);
  dump.write();
  
  BoutFinalise();
  return 0;
}
