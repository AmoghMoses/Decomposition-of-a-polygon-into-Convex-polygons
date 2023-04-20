/**
 * @file main.cpp
 * @brief The main file for the program.
 */

/*
Name : Akshat Khaitan 2020A7PS2055H
       Aditya Dhanekula 2020A7PS0205H
       Prakhar Nigam 2020A7PS0168H
       Amogh Moses 2020A7PS1199H
*/
#include <bits/stdc++.h>
#include <time.h>
using namespace std;

#include "DCEL.hpp"
#include "Rectangle.hpp"

/**
* @brief It checks if the angle formed by the 3 points is a notch.
* @param p It is pointer to the first point of the angle to be checked.
* @param q It is pointer to the second point of the angle to be checked.
* @param r It is pointer to the third point of the angle to be checked.
*/
bool check_notch(Point *p, Point *q, Point *r) // O(1) time
{
    double a = p->x;
    double b = p->y;
    double c = q->x;
    double d = q->y;
    double e = r->x;
    double f = r->y;
    double a1 = (a - c);
    double a2 = (b - d);
    double b1 = (e - c);
    double b2 = (f - d);
    double temp = a1 * b2 - a2 * b1;
    return temp < 0;
}


/**
* @brief It checks if the diagonal d is an edge of the polygon L.
* @param d It is the diagonal to be checked.
* @param L It is the polygon in which it is to be checked.
*/
//d is an edge of some polygon L1. Now we check it is common with polygon L2.
bool check(pair<int, int> d, deque<int> L)
{
    for(int i = 0; i < L.size(); i++)
    {
        if(L[i] == d.first && L[(i+1) % L.size()] == d.second)
            return true;
        if(L[i] == d.second && L[(i+1) % L.size()] == d.first)
            return true;
    }
    return false;
}

/**
* @brief It merges the decomposed polygons.
* @param dcel It is the DCEL of the polygon.
* @param decomp It is the decomposition of the polygon along with added diagonal.
*/
void merging(DCEL &dcel, vector<pair<deque<int>, pair<int, int>>> decomp) // O(N^3)
{
    int flag_outer = 0;
    do 
    {
    flag_outer = 0;
    for(int i = 0; i < decomp.size(); i++)
    {
        for(int j = i + 1;j < decomp.size(); j++)
        {
            deque<int> L1 = decomp[i].first;
            deque<int> L2 = decomp[j].first;
            pair<int, int> d1 = decomp[i].second;
            pair<int, int> d2 = decomp[j].second;
            if(check(d1, L2) == false) continue;
            int vs = d1.first;
            int vt = d1.second;
            int index_vt = 0;
            int index_vs = 0;
            deque<int> merged;
            for(int k = 0; k < L1.size(); k++){ 
                if(L1[k] == vs)
                    index_vs = k;   
                if(L1[k] == vt)
                    index_vt = k;       
                merged.push_back(L1[k]);
            }
       
            int x = L1[L1.size() - 1];
            int index = -1;
            for(int k = 0; k < L2.size(); k++)
            {
                if(L2[k] == x)
                {
                    index = k;
                    break;
                }
            }
            for(int k = 1; k < L2.size() - 1; k++){
                merged.push_back(L2[(k + index) % L2.size()]);
            }
            //angle vs : merged[vs.prev], merged[vs], merged[vs.next]  
            //angle vt : merged[vt.prev], merged[vt], merged[vt.next]

            int flag = 1;
            int n = merged.size();
            Point *p1 = dcel.points[merged[(n + (index_vs - 1)) % n]]; 
            Point *p2 = dcel.points[merged[index_vs]];
            Point *p3 = dcel.points[merged[(index_vs + 1) % n]];
            if(check_notch(p1, p2, p3))
                flag = 0;
            p1 = dcel.points[merged[(n + (index_vt - 1)) % n]]; 
            p2 = dcel.points[merged[index_vt]];
            p3 = dcel.points[merged[(index_vt + 1) % n]];
            if(flag == 1 && check_notch(p1, p2, p3))
                flag = 0;
            vector<pair<deque<int>, pair<int, int>>> new_decomp;
            if(flag == 1)
            {
                // merging possible 
                for(auto x: decomp)
                {
                    if(x.first != L1 && x.first != L2)
                        new_decomp.push_back(x);
                }
                new_decomp.push_back({merged, d2});
                decomp = new_decomp;
                flag_outer = 1;
                break;
            }
            else
            {
            continue;
            }               
        }
        if(flag_outer == 1)
            break;
    }
    } while(flag_outer == 1);

    for(auto x: decomp) {
        if(x.second.first == -1) continue;
        int v1 = x.second.first;
        int v2 = x.second.second;
        dcel.add_half_edge(v1,v2, dcel.points[v1], dcel.points[v2]);
    }
}

/**
* @brief It builds the polygon from the given points in clockwise order.
* @param dcel It is the DCEL object used to store the polygon.
* @param polygon It is the list of points of the polygon in clockwise order.
*/
void build_polygon(DCEL &dcel, const vector<Point *> &polygon) // O(V)
{
    // Add vertices to DCEL and store their indices
    vector<int> indices;
    for (int i = 0; i < polygon.size(); i++)
    {
        dcel.add_point(polygon[i]->x, polygon[i]->y);
        indices.push_back(i);
    }

    // Add half-edges to DCEL and connect them
    for (int i = 0; i < indices.size(); i++)
    {
        int j = (i + 1) % indices.size(); // index of next vertex
        Point *v1 = dcel.points[indices[i]];
        Point *v2 = dcel.points[indices[j]];
        dcel.add_half_edge(i, j, v1, v2); // adds both the half edges between
    }
    dcel.connect_half_edges();
}

/**
* @brief It checks if the given point p is inside the polygon represented by dcel.
* @param p It is pointer to the point to be checked.
* @param v It is the list of indexes of points of the polygon.
* @param dcel It is dcel object of the polygon.
*/
bool check_inside_polygon(Point *p, deque<int> v, DCEL &dcel) // O(V)
{
    double flag = -1;
    for (int i = 0; i < v.size(); i++)
    {
        Point *p1 = dcel.points[v[i]];
        Point *p2 = dcel.points[v[(i + 1) % v.size()]];
        double x = p->x;
        double y = p->y;
        double x1 = p1->x;
        double y1 = p1->y;
        double x2 = p2->x;
        double y2 = p2->y;
        if (flag == -1)
        {
            flag = (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
            if(flag == 0)
                return false;
        }
        else
        {
            double temp = (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
            if (flag * temp <= 0)
                return false;
        }
    }
    return true;
}
/**
* @brief It checks on which side does the given point lie of the line.
*/
double helper(double x1, double y1, double x2, double y2, double x, double y) // O(1)
{
    return (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
}

/**
* @brief It constructs the semiplane using the notch v and the list L.
*/
deque<int> semiplane_reduction(int v, deque<int> L, DCEL &dcel) // O(V)
{
    int v1 = L.front();
    deque<int> L1;
    double x1 = dcel.points[v1]->x;
    double y1 = dcel.points[v1]->y;
    double x2 = dcel.points[v]->x;
    double y2 = dcel.points[v]->y;
    double x = dcel.points[L.back()]->x;
    double y = dcel.points[L.back()]->y;
    int flag = -1;
    flag = helper(x1, y1, x2, y2, x, y);
    for (int i : L)
    {
        x = dcel.points[i]->x;
        y = dcel.points[i]->y;
        if (flag * helper(x1, y1, x2, y2, x, y) < 0)
            L1.push_back(i);    
    }
    return L1;
}

/**
* @brief It is the function that generates the decomposition of the given polygon into convex polygons.
*/
vector<pair<deque<int>, pair<int, int>>> polygon_decomposition(DCEL &dcel, int start) // O(V^2)
{
    vector<pair<deque<int>, pair<int, int>>> ans;
    int number_of_diagonals = 0;
    int n1 = dcel.points.size();
    deque<int> P;
    for (int i = 0; i < n1; i++)
        P.push_back(i);
    deque<int> L;
    int m = 0;
    L.push_back(P[start]);
    while (P.size() > 3)
    {
        int n = P.size();
        int v1 = L.back();
        int v2;
        int j;
        for (j = 0; j < n; j++)
            if (P[j] == v1)
                break;
        v2 = P[(j + 1) % n];
        L.clear();
        L.push_back(v1);
        L.push_back(v2);
        int i = (j + 1) % n;
        Point *p1 = dcel.points[v1];                   // First Point in the List
        Point *p2 = dcel.points[v2];                   // Secod Point in the list
        Point *p3 = dcel.points[P[i]];                 // Last point added
        Point *p4 = dcel.points[P[(i + 1) % n]];       // point I want to add
        Point *p5 = dcel.points[P[(n + (i - 1)) % n]]; // Last to Last Point Added

        // 3.3
        while (L.size() < n && !check_notch(p5, p3, p4) && !check_notch(p3, p4, p1) && !check_notch(p4, p1, p2))
        {
            L.push_back(P[(i + 1) % n]);
            p5 = p3;
            p3 = p4;
            i = (i + 1) % n;
            p4 = dcel.points[P[(i + 1) % n]];
        }

        // 3.4
        if (L.size() != P.size() && L.size() != 2)
        {

            // 3.4.1
            deque<int> temp;
            for (int j = 0; j < P.size(); j++)
            {
                int flag = 1;
                for (int k = 0; k < L.size(); k++)
                {
                    if (P[j] == L[k])
                        flag = 0;
                }
                if (flag == 1)
                    temp.push_back(P[j]);
            }
            // checking notches
            deque<int> LPVS;
            for (int k = 0; k < temp.size(); k++)
            {
                Point *p1 = dcel.points[temp[k]];
                Point *p2 = dcel.points[(temp[k] + 1) % dcel.points.size()];
                Point *p3 = dcel.points[(dcel.points.size() + (temp[k] - 1)) % dcel.points.size()];
                if (check_notch(p3, p1, p2))
                    LPVS.push_back(temp[k]);
            }
            // 3.4.2

            while (LPVS.size() > 0)
            {
                // point 1
                Rectangle *r = new Rectangle();
                for (auto i : L)
                    r->setLimit(dcel.points[i]);

                // point 2
                bool backward = false;
                // deque<int> LPVS;
                while (!backward && LPVS.size() > 0)
                {
                    int v;
                    do
                    {
                        v = LPVS.front();
                        if (r->checkInside(dcel.points[v]))
                            break;
                        else
                            LPVS.pop_front();
                    } while (LPVS.size() != 0);

                    if (LPVS.size() > 0)
                    {
                        if (check_inside_polygon(dcel.points[v], L, dcel))
                        {
                        // cout<<L.size()<<endl;
                        L = semiplane_reduction(v, L, dcel);
                        // cout<<L.size()<<endl;
                            backward = true;
                        }
                        LPVS.pop_front();
                    }

                }
            }
        }

        // 3.5 here
        if (L.back() != L[1])
        {
            int v1 = L.back();
            int v2 = L[0];
            // dcel.add_half_edge(v1, v2, dcel.points[v1], dcel.points[v2]);
            ans.push_back({L, {min(v1, v2), max(v1, v2)}});
            number_of_diagonals++;
            deque<int> temp;
            set<int> s;
            for (int i = 1; i < L.size() - 1; i++)
                s.insert(L[i]);
            for (int i = 0; i < P.size(); i++)
            {
                if (s.find(P[i]) == s.end())
                    temp.push_back(P[i]);
            }
            P = temp;
        }
    }
    return ans;
}

/**
 * @brief This is the main function of the program. Execution starts here and the necessary functions are called as required.
*/

int main()
{
    ofstream fout, fout2, fout3;
    ifstream in1;
    in1.open("input.txt");
    fout.open("output_after.txt");
    fout2.open("output_before.txt");
    fout3.open("timing.txt", ios::app);
    // start timer
    int n;
    in1 >> n;
    double min_time = INT_MAX;
    DCEL min_dcel;
    vector<Point *> polygon(n);
    vector<int> pt;
    for (int i = 0; i < n; i++)
        {
            pt.push_back(i);
            double t_x, t_y;
            in1 >> t_x >> t_y;
            polygon[i] = new Point(t_x, t_y);
        }
        //output before
        for (int i = 0; i < n; i++)
        {
            fout2 << polygon[i]->x << " " << polygon[i]->y;
            if (i != n - 1)
                fout2 << "\n";
        }
    // for (int index = 0; index < n; index++)
    // {
        DCEL dcel;        
        build_polygon(dcel, polygon);
        clock_t start;
        start = clock();
        vector<pair<deque<int>, pair<int, int>>> decomp = polygon_decomposition(dcel, 0);
        merging(dcel, decomp);
        // end timer
        clock_t end;
        end = clock();
        double time = ((end - start) / (double)CLOCKS_PER_SEC) * 1000;
        fout3 << time << endl;
        if (time < min_time)
        {
            min_dcel = dcel;
            min_time = time;
        }
//    }

    for (int i = 0; i < min_dcel.half_edges.size(); i += 2)
    {
        fout << min_dcel.points[min_dcel.half_edges[i]->origin]->x << " " << min_dcel.points[min_dcel.half_edges[i]->origin]->y << endl;
        fout << min_dcel.points[min_dcel.half_edges[i]->twin->origin]->x << " " << min_dcel.points[min_dcel.half_edges[i]->twin->origin]->y << endl;
    }
    fout.close();
    return 0;
}
