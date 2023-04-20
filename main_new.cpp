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

#include "Polygon.hpp"



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
        Polygon poly;
        DCEL dcel;        
        poly.build_polygon(dcel, polygon);
        clock_t start;
        start = clock();
        vector<pair<deque<int>, pair<int, int>>> decomp = poly.polygon_decomposition(dcel, 0);
        poly.merging(dcel, decomp);
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
