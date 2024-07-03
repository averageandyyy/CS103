#include "SetTheory.h"
#include <stdexcept>
#include <iostream>
using namespace std;

/* True or false: S in T? */
bool isElementOf(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    // (void) S; // Silence warnings about unused parameters
    // (void) T;
    // throw runtime_error("Not implemented!");

    // Check that T is a set and S can be found in T.
    if (isSet(T))
    {
        if (asSet(T).count(S))
        {
            return true;
        }
    }

    return false;
}

/* True or false: S is a subset of T? */
bool isSubsetOf(Object S, Object T) {
    // /* TODO: Delete this comment, the next three lines, and implement this function! */
    // (void) S; // Silence warnings about unused parameters
    // (void) T;
    // throw runtime_error("Not implemented!");

    // Check that both are sets and that every element in S can be found in T.
    if (isSet(S) && isSet(T))
    {
        for (Object x : asSet(S))
        {
            if (!(asSet(T).count(x)))
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

/* True or false: S and T are sets, and S n T = emptyset? */
bool areDisjointSets(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    // (void) S; // Silence warnings about unused parameters
    // (void) T;
    // throw runtime_error("Not implemented!");

    // Check that both are sets and that they have nothing in common.
    if (isSet(S) && isSet(T))
    {
        for (Object x : asSet(S))
        {
            if (asSet(T).count(x))
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

/* True or false: S = {T}? */
bool isSingletonOf(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    // (void) S; // Silence warnings about unused parameters
    // (void) T;
    // throw runtime_error("Not implemented!");

    // Check for Set, size, and presence of T
    if (isSet(S))
    {
        return asSet(S).size() == 1 && asSet(S).count(T);
    }

    return false;
}

/* True or false: S and T are sets, and S in P(T)? */
bool isElementOfPowerSet(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */

    // For S to be an element of P(T), it must be a subset of T, since P(T) contains all subsets of T.
    return isSubsetOf(S, T);
}

/* True or false: S and T are sets, and S is a subset of P(T)? */
bool isSubsetOfPowerSet(Object S, Object T) {
    // Every element in S can be found in P(T)
    /* TODO: Delete this comment, the next three lines, and implement this function! */

    // Check that every element in S is an element of P(T), using the previous function
    if (isSet(S) && isSet(T))
    {
        for (Object x : asSet(S))
        {
            if (!isElementOfPowerSet(x, T))
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

/* True or false: S and T are sets, and S is a subset of P(P(T))? */
bool isSubsetOfDoublePowerSet(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    // (void) S; // Silence warnings about unused parameters
    // (void) T;
    // return false;

    // Check that every element of S is a subset of the powerset
    if (isSet(S) && isSet(T))
    {
        for (Object x : asSet(S))
        {
            if (!(isSubsetOfPowerSet(x, T)))
            {
                return false;
            }
        }

        return true;
    }

    return false;

}
