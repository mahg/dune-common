#ifndef DUNE_COMMON_SIMD_INTERFACE_HH
#define DUNE_COMMON_SIMD_INTERFACE_HH

/** @file
 *  @brief User interface of the SIMD abstraction
 *  @ingroup SIMDLib
 *
 * This file provides the unser interface functions of the SIMD abstraction
 * layer.
 *
 * This file should never be included by users of the SIMD
 * abstraction. Include <dune/common/simd/simd.hh> instead.
 */

#include <cassert>
#include <cstddef>
#include <utility>

#include <dune/common/simd/base.hh>

namespace Dune {

  //! @brief Namespace for vectorization interface functions used by library
  //!        developers
  /**
   * @ingroup SIMDLib
   */
  namespace Simd {

    /** @addtogroup SIMDLib
     *
     * @{
     *
     * @section understand_simd Understanding SIMD types
     *
     * The (idealized) model of a SIMD type `V` used in this abstraction layer
     * is that they are fixed-length vectors of some scalar type `S`.
     * Operations and operators that take values of type `S` as arguments,
     * except for `operator,()`, should be overloaded to support values of
     * type `V` too.  These operations should apply element-wise.  If the
     * operation takes more than one argument, it should accept arbitrary
     * combinations of `V` and `S`.  The exception is the combination of `S`
     * on the left hand side and `V` on the right hand side of one of the
     * assignment operators, which does not make sense.
     *
     * The result of a boolean operation is a mask type `M`, which is a SIMD
     * type with scalar type `bool` with the same number of elements as `V`.
     * The result of all other operations is again of type `V`, or of some
     * type convertible to `V`.
     *
     * This is very similiar to `std::valarray`, with the main difference
     * being that `std::valarray` is dynamic in size, while for this
     * abstraction the size is static.
     *
     * @section simd_abstraction_limit Limitations of the Abstraction Layer
     *
     * Since the abstraction layer cannot overload operators of SIMD types
     * (that would be meddling with the domain of the library that provides
     * the SIMD types), nor provide it's own constructors, there are severe
     * limitations in what the abstraction layer guarantees.  Besides the
     * standard types, the first SIMD library supported is Vc, so that is
     * where most of the limitations stem from; see \ref SIMDVcRestrictions in
     * \ref SIMDVc.
     *
     * The biggest limitations are with masks.  In Vc masks support a very
     * restricted set of operations compared to other SIMD types, so in what
     * follows we will distinguish between masks with a very small set of
     * operations and between vectors with a larger set of operations.
     *
     * Here is a compact table of the limitations as a quick reference,
     * together with suggested workarounds for the constructs that don't work.
     * `s` denotes a scalar object/expression (i.e. of type `double` or in the
     * case of masks `bool`).  `v` denotes a vector/mask object/expression.
     * `sv` means that both scalar and vector arguments are accepted.  `V`
     * denotes a vector/mask type.  `@` means any applicable operator that is
     * not otherwise listed.
     *
     * <!-- The following table is in orgtbl format -- If you are using emacs,
     *      you may want to enable the `orgtbl` minor mode.  We substitute `|`
     *      with `¦` when describing or-operators so as to not confuse
     *      orgtbl. -->
     * \code
       |                         | Vectors | workaround                | Masks     | workaround       |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | V v(s);                 | y       |                           | y         |                  |
       | V v = s;                | y       | V v(s);                   | *N*       | V v(s);          |
       | V v{s};                 | *N*     | V v(s);                   | y         | V v(s);          |
       | V v = {s};              | *N*     | V v(s);                   | y         | V v(s);          |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | v = s;                  | y       | v = V(s);                 | *N*       | v = V(s);        |
       | v = {s};                | *N*     | v = V(s);                 | *N*       | v = V(s);        |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | v++; ++v;               | *N*     | v += Scalar<V>(1);        | y(n/a)[2] | none             |
       | v--; --v;               | *N*     | v -= Scalar<V>(1);        | n/a       | none             |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | +v; -v;                 | y       |                           | *N*       | none             |
       | !v;                     | y       |                           | y         |                  |
       | ~v;                     | y       |                           | *N*       | none             |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | sv @ sv; but see below  | y       |                           | *N*       | none             |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | s << v; s >> v;         | *N*     | v << V(s);                | *N*       | none             |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | v == v; v != v;         | y       |                           | *N* [1]   | !(v ^ v); v ^ v; |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | v & v; v ^ v; v ¦ v;    | y       |                           | y         |                  |
       | v && v; v ¦¦ v;         | *N*     | Mask<V>(v) && Mask<V>(v); | y         |                  |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | v @= sv; but see below  | y       |                           | *N*       | none             |
       | v &= v; v ^= v; v ¦= v; | y       |                           | y         |                  |
       |-------------------------+---------+---------------------------+-----------+------------------|
       | v, v;[3,4]              | *N*     | void(v), v;               | y         |                  |
     * \endcode
     *
     * Notes:
     *
     * - [1] In Vc, mask-mask `==` and `!=` operations exist, but the result
     *   is of type `bool`, i.e. a scalar.
     *
     * - [2] `++` (either kind) on bools is deprecated by the standard.
     *
     * - [3] Contrary to the other operators, the expected result for `(sv1,
     *   sv2)` is exactly `sv2`, no broadcasting applied.
     *
     * - [4] Try to avoid the use of `operator,` unless both operands are
     *   built-in types if possible.  Libraries had a tendency to overload
     *   `operator,` to provide for things like container initialization
     *   before C++11, and these overloads may still be present in the library
     *   you are using and replace the default meaning of `operator,`.
     *
     * Support levels:
     *
     * - `y`: operation generally works; some instances of the operation may
     *   not apply
     *
     * - `*N*`: operation generally does not work; some instances of the
     *   operation may not apply
     *
     * - `n/a`: operation does not apply (i.e. bitwise operations to
     *   floating-point operands, `--` (and in the future possibly `++`) to
     *   boolean operands, assignment operators to scalar left hand sides)
     */

    /** @name Basic interface
     *
     * Templates and functions in this group are directly implemented by
     * templates and functions in namespace Overloads.
     *
     * @{
     */

    //! Element type of some SIMD type
    /**
     * \tparam V The SIMD (mask or vector) type.  May not include `const`,
     *           `volatile` or reference qualifiers.
     *
     * Not all operations that access the element of a vector return (a
     * reference to) the scalar type -- some may return proxy objects instead.
     * Use `valueCast()` to make sure you are getting a prvalue of the scalar
     * type.
     *
     * Implemented by `Overloads::ScalarType`.
     */
    template<class V>
    using Scalar = typename Overloads::ScalarType<V>::type;

    //! Index vector type of some SIMD type
    /**
     * \tparam V The SIMD (mask or vector) type.  May not include `const`,
     *           `volatile` or reference qualifiers.
     *
     * The index type is a SIMD vector of integers with the same number of
     * lanes as `V`.  The signedness and size of the integers is
     * implementation defined, in particular, it may be as small as `char` --
     * this can make sense if `V` is itself a SIMD vector of `char`.
     *
     * Implemented by `Overloads::IndexType`.
     */
    template<class V>
    using Index = typename Overloads::IndexType<V>::type;

    //! Mask type type of some SIMD type
    /**
     * \tparam V The SIMD (mask or vector) type.  May not include `const`,
     *           `volatile` or reference qualifiers.
     *
     * The mask type is kind of a SIMD vector of `bool` with the same number
     * of lanes as `V`.  It results from comparison operations between values
     * of type `V`.  It is only "kind of" a SIMD vector, because the
     * guaranteed supported operations are extremely limited.  At the moment
     * only the logical operators `&&`, `||` and `!` and the "bitwise"
     * operators `&`, `^` and `|` between masks are supported, and even with
     * those operators you cannot rely on automatic broadcasting of `bool`
     * values.
     *
     * \note In particular, masks do not support comparison.  As a workaround
     *       you can use `^` instead of `!=` and `!(m1 ^ m2)` instead of `m1
     *       == m2`.  (The reason why comparison is not supported is because
     *       in Vc `==` and `!=` between masks yield a single `bool` result
     *       and not a mask.)
     *
     * Implemented by `Overloads::MaskType`.
     */
    template<class V>
    using Mask = typename Overloads::MaskType<V>::type;

    //! Number of lanes in a SIMD type
    /**
     * \tparam V The SIMD (mask or vector) type.  May not include `const`,
     *           `volatile` or reference qualifiers.
     *
     * Implemented by `Overloads::LaneCount`.
     */
    template<class V>
    constexpr std::size_t lanes()
    {
      return Overloads::LaneCount<V>::value;
    }

    //! Extract an element of a SIMD type
    /**
     * \param l Number of lane to extract
     * \param v SIMD object to extract from
     *
     * \return If `v` is a non-`const` lvalue, a reference
     *         `Scalar<decay_t<V>>&`, or a proxy object through which the
     *         element of `v` may be modified.  Overwise, `v` is a `const`
     *         lvalue or an rvalue, and the result is a prvalue (a temporary)
     *         of type `Scalar<decay_t<V>>`.
     *
     * Implemented by `Overloads::lane()`.
     */
    template<class V>
    decltype(auto) lane(std::size_t l, V &&v)
    {
      assert(l < lanes<V>());
      return lane(Overloads::ADLTag<6>{}, l, std::forward<V>(v));
    }

    //! Unproxies and returns a temporary
    /**
     * \param t A value of any value category of some scalar obtained from a
     *          SIMD type, or a proxy object denoting an element of a SIMD
     *          type.
     *
     * Many of the interface functions are allowed to return proxy objects as
     * well as references when they are passed lvalues as arguments.  This
     * makes it possible to deduce types of local variables when you want the
     * actual type, not a proxy:
     * \code
     *   auto first_value = valueCast(lane(0, v));
     * \endcode
     *
     * Implemented by `Overloads::valueCast()`.
     */
    template<class T>
    auto valueCast(T &&t)
    {
      return valueCast(Overloads::ADLTag<6>{}, std::forward<T>(t));
    }

    //! Like the ?: operator
    /**
     * Equivalent to
     * \code
     *   V result;
     *   for(std::size_t l = 0; l < lanes(mask); ++l)
     *     lane(l, result) =
     *       ( lane(l, mask) ? lane(l, ifTrue) : lane(l ifFalse) );
     *   return result;
     * \endcode
     *
     * Implemented by `Overloads::cond()`.
     */
    template<class V>
    V cond(Mask<V> mask, V ifTrue, V ifFalse)
    {
      return cond(Overloads::ADLTag<6>{}, mask, ifTrue, ifFalse);
    }

    //! Whether any entry is `true`
    /**
     * Implemented by `Overloads::anyTrue()`.
     */
    template<class Mask>
    bool anyTrue(Mask mask)
    {
      return anyTrue(Overloads::ADLTag<6>{}, mask);
    }

    //! Whether all entries are `true`
    /**
     * Implemented by `Overloads::allTrue()`.
     */
    template<class Mask>
    bool allTrue(Mask mask)
    {
      return allTrue(Overloads::ADLTag<6>{}, mask);
    }

    //! Whether any entry is `false`
    /**
     * Implemented by `Overloads::anyFalse()`.
     */
    template<class Mask>
    bool anyFalse(Mask mask)
    {
      return anyFalse(Overloads::ADLTag<6>{}, mask);
    }

    //! Whether all entries are `false`
    /**
     * Implemented by `Overloads::allFalse()`.
     */
    template<class Mask>
    bool allFalse(Mask mask)
    {
      return allFalse(Overloads::ADLTag<6>{}, mask);
    }

    //! @}

    /** @name Syntactic Sugar
     *
     * Templates and functions in this group provide syntactic sugar, they are
     * implemented using the functionality from @ref SimdInterfaceBase, and
     * are not customizable by implementations.
     *
     * @{
     */

    //! Number of lanes in a SIMD type
    /**
     * \tparam V The SIMD (mask or vector) type.
     *
     * The value of the parameter is ignored; the call is simply forwarded to
     * `lanes<V>()`.
     */
    template<class V>
    std::size_t lanes(V)
    {
      return lanes<V>();
    }

    //! @} group Syntactic Sugar

    //! @} Group SIMDLib

  } // namespace Simd
} // namespace Dune

#endif // DUNE_COMMON_SIMD_INTERFACE_HH
