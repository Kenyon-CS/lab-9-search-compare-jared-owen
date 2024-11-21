#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Sequential search
int seq_search(vector<int> &keys, int key, int &numCmp) {
    numCmp = 0;
    for (int i=0; i<keys.size(); ++i){
        ++numCmp;
        if (keys[i]==key){
            return i;
        }
    }
    return -1;
}

// Sequential search with start and stop range
int seq_search(vector<int> &keys, int key, int start, int stop, int &numCmp) {
    numCmp = 0;
    for (int i=start; i<stop; ++i){
        ++numCmp;
        if (keys[i]==key){
            return i;
        }
    }
    return -1; //Return -1 if not found
}

// Binary search
int bin_search(vector<int> &keys, int key, int &numCmp) {
    numCmp = 0;
    int left = 0, right = keys.size() - 1;

    while (left <= right) {
        ++numCmp;
        int mid = left + (right - left) / 2;

        if (keys[mid] == key) {
            return mid;
        } else if (keys[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Return -1 if not found
}


// Enhanced binary search: switches to sequential search if remaining range is < 15
int bin2_search(vector<int> &keys, int key, int &numCmp) {
numCmp = 0;
    int left = 0, right = keys.size() - 1;

    while (right - left + 1 > 15) { // If the remaining range is > 15
        ++numCmp;
        int mid = left + (right - left) / 2;

        if (keys[mid] == key) {
            return mid; 
        } else if (keys[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Switch to sequential search for smaller spans
    return seq_search(keys, key, left, right, numCmp);

}

// Test the search algorithms
int main() {
    // Initialize random seed
    srand(time(NULL));

    // Create a vector of 100,000 integers
    std::vector<int> vec;

    for (int i = 0; i < 100000; i++) {
        int iRand = rand() % 10000000;
        vec.push_back(iRand);
    }

    // Sort the vector using STL sort
    std::sort(vec.begin(), vec.end());

    // Generate 50 random numbers (may or may not be in the array)
    std::vector<int> randomKeys;
    for (int i = 0; i < 50; i++) {
        randomKeys.push_back(rand() % 10000000);
    }

    // Display table headers
    std::cout << "Search    "
              << "Found    "
              << "Seq.search    "
              << "Bin search    "
              <<"Enhanced search    " << "\n";

    // Process each random key
    for (int key : randomKeys) {
        int numCmpSeq = 0, numCmpBin = 0, numCmpEnhanced = 0;

        // Perform sequential search
        int seqIndex = seq_search(vec, key, numCmpSeq);

        // Perform binary search
        int binIndex = bin_search(vec, key, numCmpBin);

        // Perform enhanced binary search
        int enhancedIndex = bin2_search(vec, key, numCmpEnhanced);

        // Determine found value for consistency
        int foundValue = (seqIndex != -1) ? vec[seqIndex] : -1;

        // Print results for this key
        std::cout << key << "       "
                  << foundValue << "    "
                  << numCmpSeq << "             "
                  << numCmpBin << "             "
                  << numCmpEnhanced << "\n";
    }

    return 0;
}
