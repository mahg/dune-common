#ifndef DUNE_COMMON_TUPLES_MODIFIERS_HH
#define DUNE_COMMON_TUPLES_MODIFIERS_HH

#include <dune/common/static_assert.hh>

#include <dune/common/tuples/tuples.hh>

namespace Dune
{
  /** @addtogroup Tuples_MetaProgramming
   *
   * @{
   */

  /** \brief Helper template to append a type to a tuple
   *
   *  \tparam Tuple The tuple type to extend
   *  \tparam T     The type to be appended to the tuple
   *
   *  With variadic templates the generic specialization would be:
   *
   *  @code
   *  template<class... TupleArgs, class T>
   *  struct PushBackTuple<typename Dune::tuple<TupleArgs...>, T>
   *  {
   *    typedef typename Dune::tuple<TupleArgs..., T> type;
   *  };
   *  @endcode
   */
  template< class Tuple, class T>
  struct PushBackTuple
  {
    dune_static_assert(AlwaysFalse<Tuple>::value, "Attempt to use the "
                       "unspecialized version of PushBackTuple.  "
                       "PushBackTuple needs to be specialized for "
                       "each possible tuple size.  Naturally the number of "
                       "pre-defined specializations is limited arbitrarily.  "
                       "Maybe you need to raise this limit by defining some "
                       "more specializations?");

    /**
     * \brief For all specializations this is the type of a tuple with T appended.
     *
     * Suppose you have Tuple=tuple<T1, T2, ..., TN> then
     * this type is tuple<T1, T2, ..., TN, T>.
     */
    typedef Tuple type;
  };


#ifndef DOXYGEN

  template<class T>
  struct PushBackTuple< Dune::tuple<>, T>
  {
    typedef typename Dune::tuple<T> type;
  };

  template< class T1, class T>
  struct PushBackTuple< Dune::tuple<T1>, T>
  {
    typedef typename Dune::tuple<T1, T> type;
  };

  template< class T1, class T2, class T>
  struct PushBackTuple< Dune::tuple<T1, T2>, T>
  {
    typedef typename Dune::tuple<T1, T2, T> type;
  };

  template< class T1, class T2, class T3, class T>
  struct PushBackTuple< Dune::tuple<T1, T2, T3>, T>
  {
    typedef typename Dune::tuple<T1, T2, T3, T> type;
  };

  template< class T1, class T2, class T3, class T4, class T>
  struct PushBackTuple< Dune::tuple<T1, T2, T3, T4>, T>
  {
    typedef typename Dune::tuple<T1, T2, T3, T4, T> type;
  };

  template< class T1, class T2, class T3, class T4, class T5, class T>
  struct PushBackTuple< Dune::tuple<T1, T2, T3, T4, T5>, T>
  {
    typedef typename Dune::tuple<T1, T2, T3, T4, T5, T> type;
  };

  template< class T1, class T2, class T3, class T4, class T5, class T6, class T>
  struct PushBackTuple< Dune::tuple<T1, T2, T3, T4, T5, T6>, T>
  {
    typedef typename Dune::tuple<T1, T2, T3, T4, T5, T6, T> type;
  };

  template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T>
  struct PushBackTuple< Dune::tuple<T1, T2, T3, T4, T5, T6, T7>, T>
  {
    typedef typename Dune::tuple<T1, T2, T3, T4, T5, T6, T7, T> type;
  };

  template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T>
  struct PushBackTuple< Dune::tuple<T1, T2, T3, T4, T5, T6, T7, T8>, T>
  {
    typedef typename Dune::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T> type;
  };

#endif



  /** \brief Helper template to prepend a type to a tuple
   *
   *  \tparam Tuple The tuple type to extend
   *  \tparam T     The type to be prepended to the tuple
   *
   *  With variadic templates the generic specialization would be:
   *
   *  @code
   *  template<class... TupleArgs, class T>
   *  struct PushFrontTuple<typename Dune::tuple<TupleArgs...>, T>
   *  {
   *    typedef typename Dune::tuple<T, TupleArgs...> type;
   *  };
   *  @endcode
   */
  template< class Tuple, class T>
  struct PushFrontTuple
  {
    dune_static_assert(AlwaysFalse<Tuple>::value, "Attempt to use the "
                       "unspecialized version of PushFrontTuple.  "
                       "PushFrontTuple needs to be specialized for "
                       "each possible tuple size.  Naturally the number of "
                       "pre-defined specializations is limited arbitrarily.  "
                       "Maybe you need to raise this limit by defining some "
                       "more specializations?");

    /**
     * \brief For all specializations this is the type of a tuple with T prepended.
     *
     * Suppose you have Tuple=tuple<T1, T2, ..., TN> then
     * this type is tuple<T, T1, T2, ..., TN>.
     */
    typedef Tuple type;
  };


#ifndef DOXYGEN

  template<class T>
  struct PushFrontTuple< Dune::tuple<>, T>
  {
    typedef typename Dune::tuple<T> type;
  };

  template< class T1, class T>
  struct PushFrontTuple< Dune::tuple<T1>, T>
  {
    typedef typename Dune::tuple<T, T1> type;
  };

  template< class T1, class T2, class T>
  struct PushFrontTuple< Dune::tuple<T1, T2>, T>
  {
    typedef typename Dune::tuple<T, T1, T2> type;
  };

  template< class T1, class T2, class T3, class T>
  struct PushFrontTuple< Dune::tuple<T1, T2, T3>, T>
  {
    typedef typename Dune::tuple<T, T1, T2, T3> type;
  };

  template< class T1, class T2, class T3, class T4, class T>
  struct PushFrontTuple< Dune::tuple<T1, T2, T3, T4>, T>
  {
    typedef typename Dune::tuple<T, T1, T2, T3, T4> type;
  };

  template< class T1, class T2, class T3, class T4, class T5, class T>
  struct PushFrontTuple< Dune::tuple<T1, T2, T3, T4, T5>, T>
  {
    typedef typename Dune::tuple<T, T1, T2, T3, T4, T5> type;
  };

  template< class T1, class T2, class T3, class T4, class T5, class T6, class T>
  struct PushFrontTuple< Dune::tuple<T1, T2, T3, T4, T5, T6>, T>
  {
    typedef typename Dune::tuple<T, T1, T2, T3, T4, T5, T6> type;
  };

  template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T>
  struct PushFrontTuple< Dune::tuple<T1, T2, T3, T4, T5, T6, T7>, T>
  {
    typedef typename Dune::tuple<T, T1, T2, T3, T4, T5, T6, T7> type;
  };

  template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T>
  struct PushFrontTuple< Dune::tuple<T1, T2, T3, T4, T5, T6, T7, T8>, T>
  {
    typedef typename Dune::tuple<T, T1, T2, T3, T4, T5, T6, T7, T8> type;
  };

#endif



#ifndef DOXYGEN

  namespace
  {
    // CutOutTuple
    // -----------

    template< class Tuple, int begin, int length,
              class StartType = Dune::tuple<> >
    class CutOutTuple
    {
      dune_static_assert( (begin+length <= Dune::tuple_size< Tuple >::value),
                          "Can not cut out tuple of given length" );
      typedef typename Dune::PushBackTuple< StartType, Dune::tuple_element< begin, Tuple > >::type NextType;

    public:
      typedef typename CutOutTuple< Tuple, (begin+1), (length-1), NextType >::type type;
    };

    template< class Tuple, int begin, class ResultType >
    struct CutOutTuple< Tuple, begin, 0, ResultType >
    {
      typedef ResultType type;
    };

  } // namespace

#endif // #ifndef DOXYGEN



  // PopFrontTuple
  // -------------

  /** \brief Please doc me.
   *
   */
  template< class Tuple, int size = Dune::tuple_size< Tuple >::value >
  struct PopFrontTuple
  {
    dune_static_assert( (size == Dune::tuple_size< Tuple >::value),
                        "The \"size\" template parameter of PopFrontTuple "
                        "is an implementation detail and should never be "
                        "set explicitly!" );

    typedef typename CutOutTuple< Tuple, 1, (Dune::tuple_size< Tuple >::value - 1) >::type type;
  };

  template< class Tuple >
  struct PopFrontTuple< Tuple, 0 >
  {
    typedef Tuple type;
  };



  // PopBackTuple
  // ------------

  /** \brief Please doc me.
   *
   */
  template< class Tuple, int size = Dune::tuple_size< Tuple >::value >
  struct PopBackTuple
  {
    dune_static_assert( (size == Dune::tuple_size< Tuple >::value),
                        "The \"size\" template parameter of PopBackTuple "
                        "is an implementation detail and should never be "
                        "set explicitly!" );

    typedef typename CutOutTuple< Tuple, 0, (Dune::tuple_size< Tuple >::value - 1) >::type type;
  };

#ifndef DOXYGEN
  template< class Tuple >
  struct PopBackTuple< Tuple, 0 >
  {
    typedef Tuple type;
  };
#endif // #ifndef DOXYGEN



  // tuple_push_back
  // ---------------

  /** \brief Please doc me.
   *
   */
  template< class T9, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 >
  inline Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > tuple_push_back ( const Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8 > &t, T9 t9 )
  {
    return Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >( get< 0 >( t ), get< 1 >( t ), get< 2 >( t ), get< 3 >( t ), get< 4 >( t ), get< 5 >( t ), get< 6 >( t ), get< 7 >( t ), t9 );
  }



  // tuple_push_front
  // ----------------

  /** \brief Please doc me.
   *
   */
  template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
  inline Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > tuple_push_front ( const Dune::tuple< T2, T3, T4, T5, T6, T7, T8, T9 > &t, T1 t1 )
  {
    return Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 >( t1, get< 0 >( t ), get< 1 >( t ), get< 2 >( t ), get< 3 >( t ), get< 4 >( t ), get< 5 >( t ), get< 6 >( t ), get< 7 >( t ) );
  }



  // tuple_pop_back
  // --------------

  /** \brief Please doc me.
   *
   */
  template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
  inline Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8 > tuple_pop_back ( const Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > &t )
  {
    return Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8 >( get< 0 >( t ), get< 1 >( t ), get< 2 >( t ), get< 3 >( t ), get< 4 >( t ), get< 5 >( t ), get< 6 >( t ), get< 7 >( t ) );
  }



  // tuple_pop_front
  // ---------------

  /** \brief Please doc me.
   *
   */
  template< class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 >
  inline Dune::tuple< T2, T3, T4, T5, T6, T7, T8, T9 > tuple_pop_front ( const Dune::tuple< T1, T2, T3, T4, T5, T6, T7, T8, T9 > &t )
  {
    return Dune::tuple< T2, T3, T4, T5, T6, T7, T8, T9 >( get< 1 >( t ), get< 2 >( t ), get< 3 >( t ), get< 4 >( t ), get< 5 >( t ), get< 6 >( t ), get< 7 >( t ), get< 8 >( t ) );
  }



  // ReduceTuple
  // -----------

  /** \brief Apply reduce with meta binary function to template
   *
   *  For a tuple\<T0,T1,...,TN-1,TN,...\> the exported result is
   *
   *  F\< ... F\< F\< F\<Seed,T0\>\::type, T1\>\::type, T2\>\::type,  ... TN-1\>\::type
   *
   *  \tparam F Binary meta function
   *  \tparam Tuple Apply reduce operation to this tuple
   *  \tparam Seed Initial value for reduce operation
   *  \tparam N Reduce the first N tuple elements
   */
  template<
      template <class, class> class F,
      class Tuple,
      class Seed=tuple<>,
      int N=tuple_size<Tuple>::value>
  struct ReduceTuple
  {
    typedef typename ReduceTuple<F, Tuple, Seed, N-1>::type Accumulated;
    typedef typename tuple_element<N-1, Tuple>::type Value;

    //! Result of the reduce operation
    typedef typename F<Accumulated, Value>::type type;
  };

#ifndef DOXYGEN
  template< template <class, class> class F, class Tuple, class Seed>
  struct ReduceTuple<F, Tuple, Seed, 0>
  {
    //! Result of the reduce operation
    typedef Seed type;
  };
#endif // #ifndef DOXYGEN



  // JoinTuples
  // ----------

  /** \brief Join two tuples
   *
   *  For Head=tuple<T0,...,TN> and Tail=tuple<S0,...,SM>
   *  the exported result is tuple<T0,..,TN,S0,...,SM>.
   *
   *  \tparam Head Head of resulting tuple
   *  \tparam Tail Tail of resulting tuple
   */
  template<class Head, class Tail>
  struct JoinTuples
  {
    //! Result of the join operation
    typedef typename ReduceTuple< PushBackTuple, Tail, Head>::type type;
  };



  // FlattenTuple
  // ------------

  /** \brief Flatten a tuple of tuples
   *
   *  This flattens a tuple of tuples tuple<tuple<T0,...,TN>, tuple<S0,...,SM> >
   *  and exports tuple<T0,..,TN,S0,...,SM>.
   *
   *  \tparam TupleTuple A tuple of tuples
   */
  template<class TupleTuple>
  struct FlattenTuple
  {
    //! Result of the flatten operation
    typedef typename ReduceTuple< JoinTuples, TupleTuple>::type type;
  };

  /** @} */

} // namespace Dune

#include "modifiers_include.hh"

#endif // #ifndef DUNE_COMMON_TUPLES_MODIFIERS_HH
