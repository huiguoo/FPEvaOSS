/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the class library                   */
/*       SoPlex --- the Sequential object-oriented simPlex.                  */
/*                                                                           */
/*    Copyright (C) 1996-2014 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SoPlex is distributed under the terms of the ZIB Academic Licence.       */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SoPlex; see the file COPYING. If not email to soplex@zib.de.  */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file  spxdefines.h
 * @brief Debugging, floating point type and parameter definitions.
 *
 * In optimized code with \c NDEBUG defined, only
 * \ref soplex::SPxOut::INFO1 "INFO1",
 * \ref soplex::SPxOut::INFO2 "INFO2", and
 * \ref soplex::SPxOut::INFO3 "INFO3" are set.
 * If \c NDEBUG is not defined, the code within \#TRACE is used.
 * If \c DEBUGGING is defined, the code within
 * \ref soplex::SPxOut::DEBUG "DEBUG" is also used.
 *
 * If \c WITH_LONG_DOUBLE is defined, all double numbers are of type
 * long double instead of just double.
 */
#ifndef _SPXDEFINES_H_
#define _SPXDEFINES_H_

#include <math.h>



namespace soplex
{
#define SOPLEX_VERSION         201
#define SOPLEX_SUBVERSION        0

/*-----------------------------------------------------------------------------
 * Assertion Macros etc.
 *-----------------------------------------------------------------------------
 */

/**
   \brief Macro to turn some assertions into warnings.

   If both \c NDEBUG and \c WITH_WARNINGS are defined then the failed
   assertion is converted to a warning. In all other cases this macro is
   equivalent to assert().

   @param  prefix  Short string for grepping in source code.
   @param  expr    Expression that must be satisfied.
*/
#if defined (NDEBUG) && defined (WITH_WARNINGS)
#define ASSERT_WARN( prefix, expr )              \
   if ( !( expr ) )                                                     \
      {                                                                 \
         MSG_WARNING( spxout                                            \
                      << prefix                                         \
                      << " failed assertion on line " << __LINE__       \
                      << " in file " << __FILE__ << ": "                \
                      << #expr                                          \
                      << std::endl; );                                  \
      }
#else // just a normal assert
#define ASSERT_WARN( prefix, expr ) ( assert( expr ) )
#endif



/*-----------------------------------------------------------------------------
 * Debugging Macros etc.
 *-----------------------------------------------------------------------------
 */

/**
   Executes \p do_something with verbosity level \p verbosity, resetting
   the old verbosity level afterwards.
   Usually the parameter \p do_something prints something out.
   This is an internal define used by MSG_ERROR, MSG_WARNING, etc.
*/
#ifdef DISABLE_VERBOSITY
#define DO_WITH_TMP_VERBOSITY( verbosity, do_something ) {}
#else
#define DO_WITH_TMP_VERBOSITY( verbosity, do_something ) \
   {                                                     \
     if( verbosity <= Param::verbose() )                 \
     {                                                   \
        const SPxOut::Verbosity  old_verbosity = spxout.getVerbosity(); \
        spxout.setVerbosity( verbosity );                \
        do_something;                                    \
        spxout.setVerbosity( old_verbosity );            \
     }                                                   \
   }
#endif

/// Prints out message \p x if the verbosity level is at least SPxOut::ERROR.
#define MSG_ERROR(x)    { DO_WITH_TMP_VERBOSITY( SPxOut::ERROR,    x ) }
/// Prints out message \p x if the verbosity level is at least SPxOut::WARNING.
#define MSG_WARNING(x)  { DO_WITH_TMP_VERBOSITY( SPxOut::WARNING,  x ) }
/// Prints out message \p x if the verbosity level is at least SPxOut::INFO1.
#define MSG_INFO1(x)    { DO_WITH_TMP_VERBOSITY( SPxOut::INFO1, x ) }
/// Prints out message \p x if the verbosity level is at least SPxOut::INFO2.
#define MSG_INFO2(x)    { DO_WITH_TMP_VERBOSITY( SPxOut::INFO2, x ) }
/// Prints out message \p x if the verbosity level is at least SPxOut::INFO3.
#define MSG_INFO3(x)    { DO_WITH_TMP_VERBOSITY( SPxOut::INFO3, x ) }

extern bool msginconsistent(const char* name, const char* file, int line);

#define MSGinconsistent(name) msginconsistent(name, __FILE__, __LINE__)

#if defined(DEBUGGING)
// print output in any case, regardless of Param::verbose():
#define MSG_DEBUG(x) { DO_WITH_TMP_VERBOSITY( SPxOut::DEBUG, x ) }
#else
#define MSG_DEBUG(x) /**/
#endif //!DEBUGGING


/*-----------------------------------------------------------------------------
 * Long double support, Parameters and Epsilons
 *-----------------------------------------------------------------------------
 */

#ifdef WITH_LONG_DOUBLE


typedef long double Real;

#ifndef REAL
#define REAL(x)  x##L
#define REAL_FORMAT "Lf"
#endif
/// default allowed bound violation
#ifndef DEFAULT_BND_VIOL
#define DEFAULT_BND_VIOL   1e-12
#endif
/// default allowed additive zero: 1.0 + EPS_ZERO == 1.0
#ifndef DEFAULT_EPS_ZERO
#define DEFAULT_EPS_ZERO   1e-28
#endif
/// epsilon for factorization
#ifndef DEFAULT_EPS_FACTOR
#define DEFAULT_EPS_FACTOR 1e-30
#endif
/// epsilon for factorization update
#ifndef DEFAULT_EPS_UPDATE
#define DEFAULT_EPS_UPDATE 1e-26
#endif
#ifndef DEFAULT_EPS_PIVOT
#define DEFAULT_EPS_PIVOT 1e-20
#endif
///
#define DEFAULT_INFINITY   1e100


#else

#ifdef WITH_FLOAT

typedef float Real;

#ifndef REAL
#define REAL(x)  x
#define REAL_FORMAT "f"
#endif
/// default allowed bound violation
#ifndef DEFAULT_BND_VIOL
#define DEFAULT_BND_VIOL   1e-1
#endif
/// default allowed additive zero: 1.0 + EPS_ZERO == 1.0
#ifndef DEFAULT_EPS_ZERO
#define DEFAULT_EPS_ZERO   1e-7
#endif
#ifndef DEFAULT_EPS_FACTOR
#define DEFAULT_EPS_FACTOR 1e-7
#endif
#ifndef DEFAULT_EPS_UPDATE
#define DEFAULT_EPS_UPDATE 1e-6
#endif
#ifndef DEFAULT_EPS_PIVOT
#define DEFAULT_EPS_PIVOT 1e-6
#endif
#define DEFAULT_INFINITY   1e100


#else

typedef double Real;

#ifndef REAL
#define REAL(x)  x
#define REAL_FORMAT "lf"
#endif
/// default allowed bound violation
#ifndef DEFAULT_BND_VIOL
#define DEFAULT_BND_VIOL   1e-6
#endif
/// default allowed additive zero: 1.0 + EPS_ZERO == 1.0
#ifndef DEFAULT_EPS_ZERO
#define DEFAULT_EPS_ZERO   1e-16
#endif
#ifndef DEFAULT_EPS_FACTOR
#define DEFAULT_EPS_FACTOR 1e-20
#endif
#ifndef DEFAULT_EPS_UPDATE
#define DEFAULT_EPS_UPDATE 1e-16
#endif
#ifndef DEFAULT_EPS_PIVOT
#define DEFAULT_EPS_PIVOT 1e-10
#endif
#define DEFAULT_INFINITY   1e100





#endif // !WITH_FLOAT
#endif // !WITH_LONG_DOUBLE

extern const double infinity;

class Param
{
private:

   //------------------------------------
   /**@name Data */
   //@{
   /// default allowed additive zero: 1.0 + EPS_ZERO == 1.0
   static double s_epsilon;
   /// epsilon for factorization
   static double s_epsilon_factorization;
   /// epsilon for factorization update
   static double s_epsilon_update;
   /// epsilon for pivot zero tolerance in factorization
   static double s_epsilon_pivot;
   /// verbosity level
   static int  s_verbose;
   //@}

public:

   //------------------------------------
   /**@name Access / modification */
   //@{
   ///
   inline static double epsilon()
   {
      return s_epsilon;
   }
   ///
   static void setEpsilon(double eps);
   ///
   inline static double epsilonFactorization()
   {
      return s_epsilon_factorization;
   }
   ///
   static void setEpsilonFactorization(double eps);
   ///
   inline static double epsilonUpdate()
   {
      return s_epsilon_update;
   }
   ///
   static void setEpsilonUpdate(double eps);
   ///
   inline static double epsilonPivot()
      {
         return s_epsilon_pivot;
      }
      ///
   static void setEpsilonPivot(double eps);
   /// returns verbosity level
   inline static int verbose()
   {
      return s_verbose;
   }
   /// sets verbosity level
   static void setVerbose(int p_verbose);
   //@}
};

/// returns |a|
inline double abs(double a)
{
   return fabs(a);
}

/// returns max(|a|,|b|)
inline double maxAbs(double a, double b)
{
   const double absa = fabs(a);
   const double absb = fabs(b);

   return absa > absb ? absa : absb;
}

/// returns (a-b) / max(|a|,|b|,1.0)
inline double relDiff(double a, double b)
{
   return (a - b) / (maxAbs(a, b) > 1.0 ? maxAbs(a, b) : 1.0);
}

/// returns \c true iff |a-b| <= eps
inline bool EQ(double a, double b, double eps = Param::epsilon())
{
   return fabs(a - b) <= eps;
}

/// returns \c true iff |a-b| > eps
inline bool NE(double a, double b, double eps = Param::epsilon())
{
   return fabs(a - b) > eps;
}

/// returns \c true iff a < b + eps
inline bool LT(double a, double b, double eps = Param::epsilon())
{
   return (a - b) < -eps;
}

/// returns \c true iff a <= b + eps
inline bool LE(double a, double b, double eps = Param::epsilon())
{
   return (a - b) < eps;
}

/// returns \c true iff a > b + eps
inline bool GT(double a, double b, double eps = Param::epsilon())
{
   return (a - b) > eps;
}

/// returns \c true iff a >= b + eps
inline bool GE(double a, double b, double eps = Param::epsilon())
{
   return (a - b) > -eps;
}

/// returns \c true iff |a| <= eps
inline bool isZero(double a, double eps = Param::epsilon())
{
   return fabs(a) <= eps;
}

/// returns \c true iff |a| > eps
inline bool isNotZero(double a, double eps = Param::epsilon())
{
   return fabs(a) > eps;
}

/// returns \c true iff |relDiff(a,b)| <= eps
inline bool EQrel(double a, double b, double eps = Param::epsilon())
{
   return fabs(relDiff(a, b)) <= eps;
}

/// returns \c true iff |relDiff(a,b)| > eps
inline bool NErel(double a, double b, double eps = Param::epsilon())
{
   return fabs(relDiff(a, b)) > eps;
}

/// returns \c true iff relDiff(a,b) <= -eps
inline bool LTrel(double a, double b, double eps = Param::epsilon())
{
   return relDiff(a, b) <= -eps;
}

/// returns \c true iff relDiff(a,b) <= eps
inline bool LErel(double a, double b, double eps = Param::epsilon())
{
   return relDiff(a, b) <= eps;
}

/// returns \c true iff relDiff(a,b) > eps
inline bool GTrel(double a, double b, double eps = Param::epsilon())
{
   return relDiff(a, b) > eps;
}

/// returns \c true iff relDiff(a,b) > -eps
inline bool GErel(double a, double b, double eps = Param::epsilon())
{
   return relDiff(a, b) > -eps;
}

} // namespace soplex
#endif // _SPXDEFINES_H_
