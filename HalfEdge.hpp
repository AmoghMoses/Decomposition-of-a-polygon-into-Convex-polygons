

#ifndef HALFEDGE_HPP
#define HALFEDGE_HPP

#include <bits/stdc++.h>
using namespace std;

/**
 * @file HalfEdge.hpp
 * @brief This file contains the declaration of the HalfEdge class.
 */

/**
 * @class HalfEdge
 * @brief A class representing a half-edge in a doubly connected edge list (DCEL) data structure.
 *
 * The HalfEdge class contains the index of the originating vertex in the DCEL::points array, as well as pointers to the twin half-edge and the next half-edge in the face.
 */
class HalfEdge {
public:
    /**
     * @brief Construct a new HalfEdge object with the given originating vertex index.
     *
     * @param a The index of the originating vertex in the DCEL::points array.
     */
    HalfEdge(int a);

    int origin; ///< The index of the originating vertex in the DCEL::points array.
    HalfEdge* twin; ///< A pointer to the twin half-edge.
    HalfEdge* next; ///< A pointer to the next half-edge in the face.
};

/**
 * @brief Construct a new HalfEdge object with the given originating vertex index.
 *
 * @param a The index of the originating vertex in the DCEL::points array.
 */
HalfEdge::HalfEdge(int a)
{
    origin = a;
    twin = nullptr;
    next = nullptr;
}

#endif