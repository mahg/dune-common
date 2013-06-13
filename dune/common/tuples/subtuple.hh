#ifndef DUNE_COMMON_TUPLES_SUBTUPLE_HH
#define DUNE_COMMON_TUPLES_SUBTUPLE_HH

#include <dune/common/tuples/modifiers.hh>
#include <dune/common/tuples/tuples.hh>

namespace Dune
{

  // SubTuple
  // --------

  /** \class SubTuple
   *
   *  \brief Please doc me.
   */
  template< class Tuple, class Positions,
            class Seed = tuple<>, int index = 0,
            int size = tuple_size< Positions >::value >
  class SubTuple
  {
    template< class, class, class, int, int > friend class SubTuple;

    // get pass number for element to append from mapping
    static const int position = tuple_element< index, Positions >::type::value;

    // add type to seed
    typedef typename tuple_element< position, Tuple >::type AppendType;
    typedef typename PushBackTuple< Seed, AppendType >::type AccumulatedType;
    typedef SubTuple< Tuple, Positions, AccumulatedType, (index+1), size > NextType;

    static typename NextType::Type append ( Tuple &tuple, Seed &seed )
    {
      AppendType append = get< position >( tuple );
      AccumulatedType next = tuple_push_back( seed, append );
      return NextType::append( tuple, next );
    }

  public:
    typedef typename NextType::Type Type;

    static Type apply ( Tuple &tuple )
    {
      Seed seed;
      return append( tuple, seed );
    }
  };

  template< class Tuple, class Positions, class Seed, int size >
  class SubTuple< Tuple, Positions, Seed, size, size >
  {
    template< class, class, class, int, int > friend class SubTuple;

    static Seed append ( Tuple &tuple, Seed &seed ) { return seed; }

  public:
    typedef Seed Type;

    static Type apply ( Tuple & ) { return Type(); }
  };

} // namespace Dune

#endif // #ifndef DUNE_COMMON_TUPLES_SUBTUPLE_HH