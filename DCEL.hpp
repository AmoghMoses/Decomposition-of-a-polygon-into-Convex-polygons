/**
 * @file DCEL.hpp
 * @brief Defines the DCEL class used for storing and manipulating 2D planar subdivisions.
 */

#ifndef DCEL_HPP
#define DCEL_HPP

#include <bits/stdc++.h>
#include "Point.hpp"
#include "HalfEdge.hpp"
#include "Face.hpp"

using namespace std;

/**
 * @brief The DCEL class represents a doubly-connected edge list, used to store and manipulate 2D planar subdivisions.
 */

class DCEL
{
public:
    /**
     * @brief A vector of pointers to points in the DCEL.
     */
    std::vector<Point*> points;
    
    /**
     * @brief A vector of pointers to half-edges in the DCEL.
     */
    std::vector<HalfEdge*> half_edges;
    
    /**
     * @brief A vector of pointers to faces in the DCEL.
     */
    std::vector<Face*> faces;

    /**
     * @brief Adds a point to the DCEL.
     * @param x The x coordinate of the point to be added.
     * @param y The y coordinate of the point to be added.
     */
    void add_point(double x, double y);

    /**
     * @brief adds a half-edge to the DCEL.
     * @param i index of the first point of the half edge.
     * @param j index of the second point of the half edge.
     * @param v1 pointer to the first point
     * @param v2 pointer to the second point
     */
    void add_half_edge(int i, int j, Point* v1, Point* v2);

    /**
     * @brief adds a face to the DCEL and returns its index.
     * @param edge index of the edge whose face pointer is to be added.
     */
    int add_face(int edge);

    /**
     * @brief connects two half-edges together by setting their next pointers to each other.
     */
    void connect_half_edges();

};

void DCEL::add_point(double x, double y)
{
    points.emplace_back(new Point(x, y));
}

void DCEL::add_half_edge(int i, int j, Point* v1, Point* v2)
{
    HalfEdge *he1 = new HalfEdge(i);
    HalfEdge *he2 = new HalfEdge(j);
    he1->twin = he2;
    he2->twin = he1;
    he1->next = NULL;
    he2->next = NULL;
    half_edges.push_back(he1);
    half_edges.push_back(he2);   
    v1->incident_edge = he1;
}

int DCEL::add_face(int edge)
{
    Face *f = new Face(faces.size(), edge);
    faces.push_back(f);
    return faces.size() - 1;
}

void DCEL::connect_half_edges()
{
    for(int i = 0; i < half_edges.size(); i+=2)
        half_edges[i]->next = half_edges[(i+2)%half_edges.size()];
    for(int i = half_edges.size() - 1; i >= 0; i-=2)
        half_edges[i]->next = half_edges[(half_edges.size() + (i-2)) %half_edges.size()];
}

#endif