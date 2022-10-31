#include "detector_prototype.h"
#include <sstream>

int main() {
  /// creting SSSD and DSSD using DetectorFactory
  auto sssd1 = prototype::DetectorFactory::new_SSSD(63.4, 13.5);
  auto dssd1 = prototype::DetectorFactory::new_DSSD(63.4, 16.0);

  std::cout << *sssd1 << std::endl;
  std::cout << *dssd1 << std::endl;

  /// Simple lambda function to test serialize boost library
  auto clone = [](const prototype::Detector &detector) {
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << detector;
    std::string det_string = oss.str();
    std::cout << det_string << std::endl;

    std::istringstream iss(det_string);
    boost::archive::text_iarchive ia(iss);
    prototype::Detector cloned_detector;
    ia >> cloned_detector;
    return cloned_detector;
  };

  /// Creating sssd3 based on sssd2 object, using serialize
  auto sssd2 = prototype::DetectorFactory::new_SSSD(13.1, 23.2);
  sssd2->name = "SSSD2";
  auto sssd3 = clone(*sssd2);
  sssd3.name = "SSSD3";
  sssd3.thickness = 25.0;
  std::cout << *sssd2 << std::endl;
  std::cout << sssd3 << std::endl;

  /// Creating dssd3 based on dssd2 object, using serialize
  auto dssd2 = prototype::DetectorFactory::new_DSSD(13.1, 26.2);
  dssd2->name = "DSSD2";
  auto dssd3 = clone(*dssd2);
  dssd3.name = "DSSD3";
  dssd3.thickness = 1050.0;
  dssd3.geometry->distance = 28.2;
  std::cout << *dssd2 << std::endl;
  std::cout << dssd3 << std::endl;
}
