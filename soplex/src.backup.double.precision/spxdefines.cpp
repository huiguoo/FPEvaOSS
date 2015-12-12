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

/**@file  spxdefines.cpp
 * @brief Debugging, floating point type and parameter definitions.
 */
#include "spxdefines.h"
#include "assert.h"
#include "spxout.h"

namespace soplex
{

const double infinity                 = DEFAULT_INFINITY;

double Param::s_epsilon               = DEFAULT_EPS_ZERO;
double Param::s_epsilon_factorization = DEFAULT_EPS_FACTOR;
double Param::s_epsilon_update        = DEFAULT_EPS_UPDATE;
double Param::s_epsilon_pivot         = DEFAULT_EPS_PIVOT;
int  Param::s_verbose               = 1;

bool msginconsistent(const char* name, const char* file, int line)
{
   assert(name != 0);
   assert(file != 0);
   assert(line >= 0);

   MSG_ERROR( spxout << file << "(" << line << ") "
   << "Inconsistency detected in " << name << std::endl; )

   return 0;
}

void Param::setEpsilon(double eps)
{
   s_epsilon = eps;
}

void Param::setEpsilonFactorization(double eps)
{
   s_epsilon_factorization = eps;
}

void Param::setEpsilonUpdate(double eps)
{
   s_epsilon_update = eps;
}

void Param::setEpsilonPivot(double eps)
{
   s_epsilon_pivot = eps;
}

void Param::setVerbose(int p_verbose)
{
#ifndef DISABLE_VERBOSITY
   s_verbose = p_verbose;
#endif
}

} // namespace soplex
