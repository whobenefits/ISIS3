#include <iostream>
#include <cstdlib>
#include "PhotoModel.h"
#include "PhotoModelFactory.h"
#include "AtmosModel.h"
#include "AtmosModelFactory.h"
#include "Pvl.h"
#include "PvlGroup.h"
#include "IException.h"
#include "Preference.h"

using namespace Isis;

int main() {
  Isis::Preference::Preferences(true);
  double pstd;
  double trans;
  double trans0;
  double transs;
  double sbar;

  std::cout << "UNIT TEST for Anisotropic1 atmospheric function" <<
            std::endl << std::endl;

  PvlGroup algp("Algorithm");
  algp += PvlKeyword("Name", "Lambert");

  PvlObject op("PhotometricModel");
  op.addGroup(algp);

  PvlGroup alga("Algorithm");
  alga += PvlKeyword("Name", "Anisotropic1");
  alga += PvlKeyword("Tau", "0.28");
  alga += PvlKeyword("Bha", "0.85");
  alga += PvlKeyword("Hnorm", "0.003");

  PvlObject oa("AtmosphericModel");
  oa.addGroup(alga);

  Pvl pvl;
  pvl.addObject(op);
  pvl.addObject(oa);
  std::cout << pvl << std::endl << std::endl;

  try {
    PhotoModel *pm = PhotoModelFactory::Create(pvl);
    AtmosModel *am = AtmosModelFactory::Create(pvl, *pm);

    am->SetStandardConditions(true);
    std::cout << "Test phase=0.0, incidence=0.0, emission=0.0 (standard conditions) ..." << std::endl;
    am->CalcAtmEffect(0.0, 0.0, 0.0, &pstd, &trans, &trans0, &sbar, &transs);
    std::cout << "Pstd = " << pstd << std::endl;
    std::cout << "Trans = " << trans << std::endl;
    std::cout << "Trans0 = " << trans0 << std::endl;
    std::cout << "Sbar = " << sbar << std::endl << std::endl;
    am->SetStandardConditions(false);

    std::cout << "Test phase=86.7226722, incidence=51.7002388, emission=38.9414439 ..." << std::endl;
    am->CalcAtmEffect(86.7226722, 51.7002388, 38.9414439, &pstd, &trans, &trans0, &sbar, &transs);
    std::cout << "Pstd = " << pstd << std::endl;
    std::cout << "Trans = " << trans << std::endl;
    std::cout << "Trans0 = " << trans0 << std::endl;
    std::cout << "Sbar = " << sbar << std::endl << std::endl;

    std::cout << "Test phase=180.0, incidence=90.0, emission=90.0 ..." << std::endl;
    am->CalcAtmEffect(180.0, 90.0, 90.0, &pstd, &trans, &trans0, &sbar, &transs);
    std::cout << "Pstd = " << pstd << std::endl;
    std::cout << "Trans = " << trans << std::endl;
    std::cout << "Trans0 = " << trans0 << std::endl;
    std::cout << "Sbar = " << sbar << std::endl << std::endl;
  }
  catch(IException &e) {
    e.print();
  }

  return 0;
}
