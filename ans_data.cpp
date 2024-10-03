#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <utility>

using namespace std;

// Class to represent P-tree structure
class PTree {
public:
    int rootCount;
    vector<vector<int>> tree;

    PTree(int size) : rootCount(0) {
        tree.resize(size, vector<int>(size, 0));
    }

    // AND operation on P-trees
    static PTree AND(const PTree& ptree1, const PTree& ptree2) {
        int size = ptree1.tree.size();
        PTree result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.tree[i][j] = ptree1.tree[i][j] & ptree2.tree[i][j];
                result.rootCount += result.tree[i][j];
            }
        }
        return result;
    }

    // Initialize P-tree with data (for simplicity, assume binary data)
    void buildTree(const vector<vector<int>>& data) {
        int size = data.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                tree[i][j] = data[i][j];
                rootCount += data[i][j];
            }
        }
    }

    void printTree(ofstream& outfile) {
        outfile << "P-tree root count: " << rootCount << endl;
        for (const auto& row : tree) {
            for (int val : row)
                outfile << val << " ";
            outfile << endl;
        }
    }
};

// Class to represent the PARM algorithm
class PARM {
private:
    vector<PTree> bandPtrees;  // P-trees for each spectral band
    int minSupport;
    double minConfidence;
    int gridSize;
    vector<pair<vector<int>, int>> frequentItemsets;  // Store frequent itemsets and their support

public:
    PARM(int gridSize, int minSupport, double minConfidence) 
        : gridSize(gridSize), minSupport(minSupport), minConfidence(minConfidence) {}

    // Build P-trees from the dataset
    void buildPTrees(const vector<vector<vector<int>>>& data) {
        for (const auto& bandData : data) {
            PTree ptree(gridSize);
            ptree.buildTree(bandData);
            bandPtrees.push_back(ptree);
        }
    }

    // Function to mine frequent itemsets
    void mineFrequentItemsets(ofstream& outfile) {
        // For simplicity, assume a 2-band association rule mining scenario
        for (int i = 0; i < bandPtrees.size() - 1; i++) {
            for (int j = i + 1; j < bandPtrees.size(); j++) {
                // Perform AND operation between two bands
                PTree result = PTree::AND(bandPtrees[i], bandPtrees[j]);
                if (result.rootCount >= minSupport) {
                    outfile << "Frequent itemset found between band " << i << " and band " << j << endl;
                    result.printTree(outfile);
                    frequentItemsets.push_back({{i, j}, result.rootCount});
                }
            }
        }
    }

    // Function to generate association rules from frequent itemsets
    void generateAssociationRules(ofstream& outfile) {
        outfile << "\nAssociation Rules:\n";
        
        // Iterate over all frequent itemsets
        for (const auto& itemsetSupportPair : frequentItemsets) {
            const vector<int>& itemset = itemsetSupportPair.first;
            int supportXY = itemsetSupportPair.second;

            // For each itemset, generate all possible non-empty subsets
            for (int i = 1; i < (1 << itemset.size()); ++i) {
                vector<int> X, Y;

                // Split itemset into two subsets: X and Y
                for (int j = 0; j < itemset.size(); ++j) {
                    if (i & (1 << j)) {
                        X.push_back(itemset[j]);
                    } else {
                        Y.push_back(itemset[j]);
                    }
                }

                // Make sure both X and Y are non-empty to form a valid rule
                if (X.empty() || Y.empty()) continue;

                // Calculate support for X (assuming X is a subset of the original bands)
                int supportX = bandPtrees[X[0]].rootCount;  // Here, you may want to improve by finding the actual support of X
                
                // Calculate confidence
                double confidence = static_cast<double>(supportXY) / supportX;
                
                // If confidence meets the threshold, output the rule
                if (confidence >= minConfidence) {
                    // Print the rule
                    outfile << "Rule: {";
                    for (int xi : X) outfile << xi << " ";
                    outfile << "} -> {";
                    for (int yi : Y) outfile << yi << " ";
                    outfile << "} with confidence: " << confidence * 100 << "%\n";
                }
            }
        }
    }
};

// Main function to test the implementation
int main() {
    int gridSize = 6;
    int minSupport = 2;
    double minConfidence = 0.3;  // Set the minimum confidence threshold

    // Input from data.txt
    ifstream infile("data.txt");
    if (!infile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    // Read data from file
    vector<vector<vector<int>>> dataset;
    for (int i = 0; i < 4; ++i) {  // Assuming 4 bands in the dataset
        vector<vector<int>> band(gridSize, vector<int>(gridSize, 0));
        for (int j = 0; j < gridSize; ++j) {
            for (int k = 0; k < gridSize; ++k) {
                infile >> band[j][k];
            }
        }
        dataset.push_back(band);
    }
    infile.close();

    // Output to ans.txt
    ofstream outfile("ans.txt");
    if (!outfile) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    PARM parm(gridSize, minSupport, minConfidence);

    // Build P-trees from the dataset
    parm.buildPTrees(dataset);

    // Mine frequent itemsets based on P-tree AND operation
    parm.mineFrequentItemsets(outfile);

    // Generate association rules from the frequent itemsets
    parm.generateAssociationRules(outfile);

    outfile.close();

    return 0;
}

