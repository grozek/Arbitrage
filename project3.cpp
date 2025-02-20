/*
 * CSC-301
 * project3.cpp
 * Fall 2022
 *
 * Partner 1: Gabriela Roznawska
 * Partner 2: --
 * Date: November 11th 2024
 */

#include "project3.hpp"
#include <cmath>
#include <algorithm>
using namespace std;

/*
 * createAdjacencyMatrix
 */
vector<double> createAdjacencyMatrix(vector<double> &rates, 
                                     vector<string> &currencies) {
    vector<double> adjMatrix(rates);
    for(int i=0; i<currencies.size() ; i++){
        adjMatrix[i] = -log10(adjMatrix[i]);
     }
    return adjMatrix;
}




/*
 * detectArbitrage
 */
vector<int> detectArbitrage(vector<double> &adjMatrix, 
                            vector<string> &currencies, 
                            double tol) {
  int n = currencies.size();
    // Get the number of vertices and initialize the dist and prev values.
    // I assume the distances/previous are set to all elements, and do not need
  // to iterate through the whole vector
  //for(int i=0; i<n; i++){ 
    vector<double> distances( n, numeric_limits<double>::infinity() );
    vector<int> previous( n, -1 );
    //}
    bool negativeDetector = false;
    int cycleIndex = -1;
    // Create the cycle.
    vector<int> cycle;
    distances[0]=0;
    for (int i=0; i<n ; i++){
      //instead for (double vertex: adjMatrix))
      for (int j=0; j < n; j++){//curr
        // instead of (double neighbor : vertex)
        // we know how many neighbor there are (or can decide by the n/m of adjMatrix)!
        for (int k=0; k<n; k++){//neighbor
          //using i for distances, cause they are at the same index at distances
          // as in adjMatrix (i can do that for vertex, but not for neighbor). What should i do???
          // for now use i+1 for neighbor, but i know its wrong
          // asssuming that length(vertex,neighbor) is adjMatrix[i]
          if (distances[k] > distances[j] + adjMatrix[j*n+k] + tol){
            distances[k] = distances[j] + adjMatrix[j*n+k];
            previous[k] = j;
            if (i == n-1){
              negativeDetector = true;
              cycleIndex = k;
            }
          }
        }
      }
    }
    if (negativeDetector == true){
       int currIndex = previous[cycleIndex];
       cycle.push_back(cycleIndex);
       while (count(cycle.begin(),cycle.end(),currIndex)<0){//while not in cycle
        cycle.push_back(currIndex);
        currIndex = previous[currIndex];
      }
    }
    //will need to cut of the excess elments, find the first occurence (find) and delete elements before 
    // reverse the cycle
    
    // Return the cycle.
    return cycle;
}



    /*
       for (vertex neighbor : vertex){
          if (neighbor.distances > vertex.distances + length(vertex,neighbor) + tol){
            neighbor.distances = vertex.distances + length(vertex,neighbor);
            neighbor.previous = vertex;
            if (i == n-1){
              negativeDetector = true;
              cycleIndex = neigbor.previous;
              }
        }
      }
       */
