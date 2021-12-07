#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>
#include "Omega_h_library.hpp"
#include "Omega_h_array_ops.hpp"
//#include "Omega_h_sort.hpp"

template <typename T, Omega_h::Int N>
struct CompareKeySets {
  T const* keys_;
  CompareKeySets(T const* keys) : keys_(keys) {}
  OMEGA_H_INLINE bool operator()(const Omega_h::LO& a, const Omega_h::LO& b) const {
    for (Omega_h::Int i = 0; i < N; ++i) {
      T x = keys_[a * N + i];
      T y = keys_[b * N + i];
      if (x != y) return x < y;
    }
    return false;
  }
};

int main(int argc, char** argv) {
  using namespace Omega_h;
  auto lib = Library(&argc, &argv);
  auto world = lib.world();
  {
    auto space = Kokkos::Experimental::SYCL();
    const auto q = *space.impl_internal_space_instance()->m_queue;

    using namespace oneapi::dpl::execution;
    using namespace sycl;
    auto policy = make_device_policy(q);

    {
    Write<LO> perm = {43, 0, 3};
    LOs expected = {0, 3, 43};
    oneapi::dpl::sort(
        policy, perm.data(), perm.data() + perm.size(),
        [](auto lhs, auto rhs) { return lhs < rhs; });

    Read<LO> r_expected(expected);
    Read<LO> r_perm(perm);
    OMEGA_H_CHECK(r_perm == r_expected);
    }

    {
    Write<LO> perm = {0,1};
    LOs keys = {0,2,0,1};
    LO const* keyptr = keys.data();
    auto cmp = CompareKeySets<LO,2>(keyptr);
    LOs expected = {1, 0};
    oneapi::dpl::sort(policy,
        perm.data(), perm.data() + perm.size(), cmp);

    Read<LO> r_expected(expected);
    Read<LO> r_perm(perm);
    OMEGA_H_CHECK(r_perm == r_expected);
    }

  }
//  }
//  {
//    LOs a({0, 2, 0, 1});
//    LOs perm = sort_by_keys(a, 2);
//    OMEGA_H_CHECK(perm == LOs({1, 0}));
//  }
//  {
//    LOs a({0, 2, 1, 1});
//    LOs perm = sort_by_keys(a, 2);
//    OMEGA_H_CHECK(perm == LOs({0, 1}));
//  }
//  {
//    LOs a({1, 2, 3, 1, 2, 2, 3, 0, 0});
//    LOs perm = sort_by_keys(a, 3);
//    OMEGA_H_CHECK(perm == LOs({1, 0, 2}));
//  }
  return 0;
}
