#ifndef FACE_HPP
#define FACE_HPP

/**
 * @file Face.hpp
 * @brief This file contains the declaration of the Face class.
 */

/**
 * @class Face
 * @brief A class representing a face in a doubly connected edge list (DCEL) data structure.
 *
 * The Face class contains the id of the face and the index of a half-edge on the boundary of the face in the DCEL::half_edges array.
 */
class Face {
public:
    /**
     * @brief Construct a new Face object with the given id and edge index.
     *
     * @param a The id of the face.
     * @param b The index of a half-edge on the boundary of the face in the DCEL::half_edges array.
     */
    Face(int a, int b);

    int id; ///< The id of the face.
    int edge; ///< The index of a half-edge on the boundary of the face in the DCEL::half_edges array.
};

/**
 * @brief Construct a new Face object with the given id and edge index.
 *
 * @param a The id of the face.
 * @param b The index of a half-edge on the boundary of the face in the DCEL::half_edges array.
 */
Face::Face(int a, int b)
{
    id = a;
    edge = b;
}


#endif

