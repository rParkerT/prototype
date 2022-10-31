#ifndef DETECTORPROTOTYPE_H_
#define DETECTORPROTOTYPE_H_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace prototype {

/**
 * Implementation of the Geometry structure.
 *
 * Geometry structure describes geometry of the detector, it's theta angle and
 * distance from the target.
 *
 */
struct Geometry {
  /// Theta angle of the detector
  float theta;
  /// Distance of the detector from target
  float distance;

  /// Default constructor
  Geometry() {}

  /**
   * Constructor of Geometry
   *
   * @param theta of detector
   * @param distance of detector
   */
  Geometry(const float theta, const float distance)
      : theta{theta}, distance{distance} {}

  /// Default destructor
  ~Geometry() {}

  /**
   * Ostream operator overloading, used to display values of Geometry
   *
   * @param os ostream object
   * @param obj Geometry object
   */
  friend std::ostream &operator<<(std::ostream &os, const Geometry &obj) {
    return os << "theta: " << obj.theta << " distance: " << obj.distance;
  }

  /// Details about library:
  /// https://theboostcpplibraries.com/boost.serialization
  friend class boost::serialization::access;

  /// Splitting serialize in save and load function. save converts Geometry
  /// object in sequence of bytes.
  template <class archive>
  void save(archive &ar, const unsigned int version) const {
    ar << theta;
    ar << distance;
  }
  /// load restores Geometry object.
  template <class archive> void load(archive &ar, const unsigned int version) {
    ar >> theta;
    ar >> distance;
  }
  /// The macro BOOST_SERIALIZATION_SPLIT_MEMBER() generates code which invokes
  /// the save or load depending on whether the archive is used for saving or
  /// loading.
  BOOST_SERIALIZATION_SPLIT_MEMBER();
};

/**
 * Implementation of the Detector structure.
 *
 * Detector structure describes name, thickness and has a pointer on Geometry
 * structure of the detector.
 *
 */
struct Detector {
  /// Name of the detector
  std::string name{};
  /// Thickness of the detector
  float thickness{0};
  /// Pointer to Geometry struct of the detector
  Geometry *geometry{nullptr};

  /// Default constructor
  Detector() {}

  /**
   * Constructor of Detector
   *
   * @param name of detector
   * @param thickness of detector
   * @param geometry of detector
   */
  Detector(const std::string &name, float thickness, Geometry *geometry)
      : name{name}, thickness{thickness} {
    this->geometry = new Geometry(geometry->theta, geometry->distance);
  }

  /**
   * Copy Constructor of Detector
   *
   * @param other Detector object to be copied
   */
  Detector(const Detector &other)
      : name{other.name}, thickness{other.thickness} {
    geometry = new Geometry(other.geometry->theta, other.geometry->distance);
  }

  /**
   * Destructor of Detector
   *
   * deletes geometry, raw pointer
   */
  ~Detector() { delete geometry; }

  /**
   * Ostream operator overloading, used to display values of Detector
   *
   * @param os ostream object
   * @param obj Detector object
   */
  friend std::ostream &operator<<(std::ostream &os, const Detector &obj) {
    return os << "name: " << obj.name << ", thickness: " << obj.thickness
              << " (um), geometry: " << *obj.geometry;
  }

  /// Details about library:
  /// https://theboostcpplibraries.com/boost.serialization
  friend class boost::serialization::access;

  /// Splitting serialize in save and load function. save converts Geometry
  /// object in sequence of bytes.
  template <class archive>
  void save(archive &ar, const unsigned int version) const {
    ar << name;
    ar << thickness;
    ar << geometry;
  }
  /// load restores Geometry object.
  template <class archive> void load(archive &ar, const unsigned version) {
    ar >> name;
    ar >> thickness;
    ar >> geometry;
  }
  /// The macro BOOST_SERIALIZATION_SPLIT_MEMBER() generates code which invokes
  /// the save or load depending on whether the archive is used for saving or
  /// loading.
  BOOST_SERIALIZATION_SPLIT_MEMBER();
};

/**
 * Implementation of the DetectorFactory structure.
 *
 * Creates prototypes of two different types of detectors - SSSD and DSSD.
 *
 */
struct DetectorFactory {
  /**
   * Prototype function that creates new SSSD detector, with given theta and
   * distance.
   *
   * @param theta of detector
   * @param distance of detector from th target
   * @return created unique_ptr to newly created SSSD detector
   */
  static std::unique_ptr<Detector> new_SSSD(float theta, float distance) {
    Geometry *geometry = new Geometry{0.0, 0.0};
    static Detector SSSD{"SSSD", 50.0, geometry};
    delete geometry;
    return new_detector(theta, distance, SSSD);
  }

  /**
   * Prototype function that creates new DSSD detector, with given theta and
   * distance.
   *
   * @param theta of detector
   * @param distance of detector from th target
   * @return created unique_ptr to newly created DSSD detector
   */
  static std::unique_ptr<Detector> new_DSSD(float theta, float distance) {
    Geometry *geometry = new Geometry{0.0, 0.0};
    static Detector DSSD{"DSSD", 1000.0, geometry};
    delete geometry;
    return new_detector(theta, distance, DSSD);
  }

  /**
   * Prototype function that creates new detector, with given theta,
   * distance and detector prototype, SSSD or DSSD.
   *
   * @param theta of detector
   * @param distance of detector from th target
   * @param proto detector prototype , SSSD or DSSD
   * @return created unique_ptr to newly created SSSD/DSSD detector
   */
  static std::unique_ptr<Detector> new_detector(float theta, float distance,
                                                Detector &proto) {
    auto result = std::make_unique<Detector>(proto);
    result->geometry->theta = theta;
    result->geometry->distance = distance;
    return result;
  }
};

} // namespace prototype

#endif /* DETECTORPROTOTYPE_H_ */
