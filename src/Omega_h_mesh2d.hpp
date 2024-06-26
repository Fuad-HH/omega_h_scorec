#ifndef OMEGA_H_2DMESH_HPP
#define OMEGA_H_2DMESH_HPP

#include <Omega_h_mesh.hpp>

namespace Omega_h {

class Mesh2D final : public Mesh {
public:
  Mesh2D() = default;
  explicit Mesh2D(Library* library) : Mesh(library) {}

  void set_dim(Int dim_in) override;

  [[nodiscard]] inline Int dim() const override {
    OMEGA_H_CHECK(0 <= dim_ && dim_ <= 2);
    return dim_;
  }
};

} // Omega_h

#endif //OMEGA_H_2DMESH_HPP
