// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_ALU3DGRIDMAPPINGS_HH
#define DUNE_ALU3DGRIDMAPPINGS_HH

// System includes

// Dune includes
#include <dune/common/fvector.hh>
#include <dune/common/fmatrix.hh>

// Local includes
#include "alu3dinclude.hh"

namespace Dune {

  //! A trilinear mapping from the Dune reference hexahedron into the physical
  //! space (same as in mapp_cube_3d.h, but for a different reference hexahedron)
  class TrilinearMapping {
    typedef FieldVector<double, 3> coord_t;
    typedef FieldMatrix<double, 3, 3> mat_t;
    static const double _epsilon ;

    const coord_t& p0;
    const coord_t& p1;
    const coord_t& p2;
    const coord_t& p3;
    const coord_t& p4;
    const coord_t& p5;
    const coord_t& p6;
    const coord_t& p7;

    double a [8][3] ;
    mat_t Df;
    mat_t Dfi;
    double DetDf ;
    void linear (const coord_t&) ;
    void inverse (const coord_t&) ;
  public:
    TrilinearMapping (const coord_t&, const coord_t&,
                      const coord_t&, const coord_t&,
                      const coord_t&, const coord_t&,
                      const coord_t&, const coord_t&);
    TrilinearMapping (const TrilinearMapping &) ;
    ~TrilinearMapping () {}
    double det (const coord_t&) ;
    mat_t jacobianInverse(const coord_t&);
    void map2world (const coord_t&, coord_t&) const ;
    void map2world (const double , const double , const double ,
                    coord_t&) const ;
    void world2map (const coord_t&, coord_t&) ;
  };

  //! A bilinear surface mapping
  class BilinearSurfaceMapping {
    typedef FieldVector<double, 3> coord3_t;
    typedef FieldVector<double, 2> coord2_t;
    const coord3_t& _p0;
    const coord3_t& _p1;
    const coord3_t& _p2;
    const coord3_t& _p3;
    double _b [4][3] ;
    double _n [3][3] ;
  public:
    BilinearSurfaceMapping (const coord3_t&, const coord3_t&,
                            const coord3_t&, const coord3_t&) ;
    BilinearSurfaceMapping (const BilinearSurfaceMapping &) ;
    ~BilinearSurfaceMapping () {}
    void map2world(const coord2_t&, coord3_t&) const ;
    void map2world(double x, double y, coord3_t&) const ;
    void normal(const coord2_t&, coord3_t&) const ;
  } ;

  //! General form of non-conforming face mapping
  //! This class is empty and needs to be specialised
  template <ALU3dGridElementType type>
  class NonConformingFaceMapping {};

  //! Non-conforming face mappings for tetrahedra
  template <>
  class NonConformingFaceMapping<tetra> {
  private:
    //- private typedefs and enums
  public:
    //- public typedefs and enums
    typedef FieldVector<alu3d_ctype, 3> CoordinateType;
    typedef ALU3DSPACE Hface3RuleType RefinementRuleType;

  public:
    //- public interface methods
    NonConformingFaceMapping(RefinementRuleType rule,
                             int nChild);
    NonConformingFaceMapping(const NonConformingFaceMapping<tetra>& orig);
    ~NonConformingFaceMapping();

    void child2parent(const CoordinateType& childCoordinates,
                      CoordinateType& parentCoordinates) const ;

  private:
    void child2parentNosplit(const CoordinateType& childCoordinates,
                             CoordinateType& parentCoordinates) const;
    void child2parentE01(const CoordinateType& childCoordinates,
                         CoordinateType& parentCoordinates) const;
    void child2parentE12(const CoordinateType& childCoordinates,
                         CoordinateType& parentCoordinates) const;
    void child2parentE20(const CoordinateType& childCoordinates,
                         CoordinateType& parentCoordinates) const;
    void child2parentIso4(const CoordinateType& childCoordinates,
                          CoordinateType& parentCoordinates) const;
  private:
    //- private data
    RefinementRuleType rule_;
    int nChild_;
  };

  //! Non-conforming face mappings for hexahedra
  template <>
  class NonConformingFaceMapping<hexa> {
  private:
    //- private typedefs and enums
  public:
    //- public typedefs and enums
    typedef FieldVector<alu3d_ctype, 2> CoordinateType;
    typedef ALU3DSPACE Hface4RuleType RefinementRuleType;
  public:
    NonConformingFaceMapping(RefinementRuleType rule, int nChild);
    NonConformingFaceMapping(const NonConformingFaceMapping<hexa>& orig);
    ~NonConformingFaceMapping();

    void child2parent(const CoordinateType& childCoordinates,
                      CoordinateType& parentCoordinates) const;
  private:
    void child2parentNosplit(const CoordinateType& childCoordinates,
                             CoordinateType& parentCoordinates) const;
    void child2parentIso4(const CoordinateType& childCoordinates,
                          CoordinateType& parentCoordinates) const;

  private:
    RefinementRuleType rule_;
    int nChild_;
  };

} // end namespace Dune

#include "mappings_imp.cc"

#endif
