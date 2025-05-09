
#include<bits/stdc++.h>
using namespace std;


class VotingSystem {
private:
    vector<string> candidateNames; // Array to store candidate names (Dynamic array)
    vector<int> votes;            // Array to store votes for each candidate (Dynamic array)


public:
    void setupCandidates(int numCandidates) {
        candidateNames.resize(numCandidates); // Dynamically resizing the vector (Dynamic array)
        votes.resize(numCandidates, 0);       // Dynamically resizing the vector (with default vote count as 0)
        cout << endl << "    Enter the names of " << numCandidates << " candidates:" << endl;
        for (int i = 0; i < numCandidates; i++) {
            cout << "    Candidate " << (i + 1) << ": ";
            cin >> candidateNames[i];
        }
    }


    vector<string>& getCandidateNames() {
        return candidateNames; // Returning the reference of the candidates list (Dynamic array)
    }


    void recordVote(int voterId, int vote) {
        if (vote > 0 && vote <= (int)candidateNames.size()) {
            votes[vote - 1]++; // Increment the vote for the selected candidate
            cout << endl << "    Thank you! Your vote has been recorded for " << candidateNames[vote - 1] << "." << endl;
        } else {
            cout << endl << "    Invalid vote! Your vote could not be recorded." << endl;
        }


        // Clear screen after vote (platform-dependent command)
        #if defined(_WIN32) || defined(_WIN64)
            system("cls"); // For Windows
        #else
            system("clear"); // For Linux/macOS
        #endif
    }


    void displayResults(const string& adminPassword) {
        string enteredPassword;
        cout << endl << "Enter the admin password to view results: ";
        cin >> enteredPassword;
        if (enteredPassword == adminPassword) {
            ofstream outFile("ElectionResults.txt"); // File handling (using file stream)


            cout << endl << "Election Results:" << endl;
            cout << "-------------------------------------" << endl;
            outFile << "Election Results:\n";
            outFile << "-------------------------------------\n";


            // Display results and write them to a file
            for (size_t i = 0; i < candidateNames.size(); i++) {
                cout << "Candidate " << candidateNames[i] << " received " << votes[i] << " votes." << endl;
                outFile << "Candidate " << candidateNames[i] << " received " << votes[i] << " votes.\n";
            }


            // Determine the winner or if it's a draw (use of simple algorithm)
            int maxVotes = *max_element(votes.begin(), votes.end()); // Using algorithm: max_element to find the candidate with the most votes
            vector<string> winners; // To store the candidates with maximum votes
            for (size_t i = 0; i < votes.size(); i++) {
                if (votes[i] == maxVotes) {
                    winners.push_back(candidateNames[i]); // Collect the winners
                }
            }


            cout << "\nResults Summary:" << endl;
            outFile << "\nResults Summary:\n";


            if (winners.size() > 1) { // If multiple winners, it's a draw
                cout << "It's a draw between the following candidates:" << endl;
                outFile << "It's a draw between the following candidates:\n";
                for (const string& winner : winners) {
                    cout << "- " << winner << endl;
                    outFile << "- " << winner << "\n";
                }
            } else {
                cout << "The winner is: " << winners[0] << " with " << maxVotes << " votes!" << endl;
                outFile << "The winner is: " << winners[0] << " with " << maxVotes << " votes!\n";
            }


            outFile.close(); // Close the file
            cout << "\nResults have been saved to 'ElectionResults.txt'." << endl;
        } else {
            cout << endl << "Incorrect password! Access denied." << endl;
        }
    }


    void sortCandidatesByVotes() {
        priority_queue<pair<int, string>> pq; // Using a priority queue (max-heap) to sort candidates by votes
        for (size_t i = 0; i < candidateNames.size(); i++) {
            pq.push({votes[i], candidateNames[i]}); // Storing the votes with candidate names in the priority queue
        }


        cout << "\nCandidates sorted by votes:" << endl;
        // Extracting candidates from the priority queue in sorted order (highest votes first)
        while (!pq.empty()) {
            auto [voteCount, name] = pq.top(); // Pairing votes with candidate names
            cout << name << " with " << voteCount << " votes." << endl;
            pq.pop(); // Pop the top candidate from the queue
        }
    }


    void demonstrateGraph() {
        unordered_map<int, list<int>> graph; // Using unordered_map (hash map) to represent a graph
        graph[1] = {2, 3}; // Node 1 connects to nodes 2 and 3
        graph[2] = {1, 4}; // Node 2 connects to nodes 1 and 4
        graph[3] = {1};    // Node 3 connects to node 1
        graph[4] = {2};    // Node 4 connects to node 2


        cout << "\nGraph representation:" << endl;
        // Iterating through the graph (unordered_map) to display connections
        for (auto& [node, neighbors] : graph) {
            cout << "Node " << node << " connects to: ";
            for (int neighbor : neighbors) { // Traversing the list of neighbors
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};


int main() {
    VotingSystem system; // Create the VotingSystem object
    int numCandidates, numStudents;
    string pass;
    const string adminPassword = "hehe"; // Admin password


    cout << endl << "                     Online Voting System / Election System                   " << endl;
    cout << "                     _______________                   " << endl;
    cout << endl << "                        :::::::::: ADMIN PANEL ::::::::::" << endl;
    cout << endl << "=================================================================================" << endl;
    cout << endl;
    cout << endl << "    Number of Candidates: ";
    cin >> numCandidates;


    if (numCandidates > 1) {
        system.setupCandidates(numCandidates); // Setup candidates (Dynamic array usage)


        cout << "    Number of Students: ";
        cin >> numStudents;
        cout << endl << "  Thank You Admin! We are going to start our election with " << numStudents << " students and " << numCandidates << " candidates." << endl;
        cout << endl << "                            Enter The Password: ";
        cin >> pass;


        while (pass != adminPassword) {
            cout << endl << "                            Wrong Password! Try Again." << endl;
            cout << endl << "                       Enter The Correct Password: ";
            cin >> pass;
        }


        for (int i = 1; i <= numStudents; i++) {
            cout << endl << "                     Online Voting System / Election System                   " << endl;
            cout << "                     _______________                   " << endl;
            cout << endl << "                        :::::::::: VOTING PANEL ::::::::::" << endl;
            cout << endl << "                                   Student - " << i << endl;
            cout << endl << "=================================================================================" << endl;


            vector<string> &candidateNames = system.getCandidateNames(); // Dynamic array of candidate names
            for (size_t j = 0; j < candidateNames.size(); j++) {
                cout << "                              Press " << j + 1 << " For " << candidateNames[j] << endl;
            }


            cout << endl << "    Now, Please Put Your Vote (1-" << candidateNames.size() << "): ";
            int vote;
            cin >> vote;
            system.recordVote(i, vote); // Record vote for the student
        }


        system.displayResults(adminPassword); // Display results
        system.sortCandidatesByVotes(); // Display sorted candidates
        system.demonstrateGraph();      // Demonstrate graph functionality


    } else {
        cout << endl << "Sorry! Number of candidates must be more than one person." << endl;
    }
}
