#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

vector<int> getNeighbors(int state)
{
    // don't touch this code please ;_;
    vector<int> neighbors;
    string strState = to_string(state);

    if ((state / 100000000) == 0)
        strState.insert(0, "0");

    int indexZero = strState.find('0');
    int rowZero = indexZero / 3;
    int columnZero = indexZero % 3;

    int rowTmp, colTmp, newIndexZero;

    string sTemp = "";
    rowTmp = rowZero - 1;
    colTmp = columnZero;
    if ((rowTmp <= 2) && (rowTmp >= 0) && (colTmp <= 2) && (colTmp >= 0))
    {
        sTemp = strState;
        newIndexZero = rowTmp * 3 + colTmp;
        sTemp[indexZero] = sTemp[newIndexZero];
        sTemp[newIndexZero] = '0';
        neighbors.push_back(stoi(sTemp));
    }

    sTemp = "";
    rowTmp = rowZero + 1;
    colTmp = columnZero;
    if ((rowTmp <= 2) && (rowTmp >= 0) && (colTmp <= 2) && (colTmp >= 0))
    {
        sTemp = strState;
        newIndexZero = rowTmp * 3 + colTmp;
        sTemp[indexZero] = sTemp[newIndexZero];
        sTemp[newIndexZero] = '0';
        neighbors.push_back(stoi(sTemp));
    }

    sTemp = "";
    rowTmp = rowZero;
    colTmp = columnZero - 1;
    if ((rowTmp <= 2) && (rowTmp >= 0) && (colTmp <= 2) && (colTmp >= 0))
    {
        sTemp = strState;
        newIndexZero = rowTmp * 3 + colTmp;
        sTemp[indexZero] = sTemp[newIndexZero];
        sTemp[newIndexZero] = '0';
        neighbors.push_back(stoi(sTemp));
    }

    sTemp = "";
    rowTmp = rowZero;
    colTmp = columnZero + 1;
    if ((rowTmp <= 2) && (rowTmp >= 0) && (colTmp <= 2) && (colTmp >= 0))
    {
        sTemp = strState;
        newIndexZero = rowTmp * 3 + colTmp;
        sTemp[indexZero] = sTemp[newIndexZero];
        sTemp[newIndexZero] = '0';
        neighbors.push_back(stoi(sTemp));
    }

    return neighbors;
}

int main()
{

    int inState;
    cin >> inState;

    unordered_map<int, int> parentMap; // bec insertion is O(1)
    vector<int> frontier;
    set<int> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
    set<int> isInFrontier;
    vector<int> neighbors;
    // vector<int> neighbors;
    map<long long, long long> depthMap;
    int state;
    bool answerExist = false;
    int depth = 0, maxDepth = 0;

    frontier.push_back(inState);
    parentMap[inState] = inState;
    // isInFrontier[inState] = true;
    isInFrontier.emplace(inState);
    // int state;

    while (!frontier.empty())
    {
        state = frontier.back();
        frontier.pop_back();
        // frontier.erase(frontier.begin());
        isInFrontier.emplace(state);
        // cout << "s = " << state << endl;
        // explored[state] = true;
        explored.emplace(state);

        if (state == 12345678)
        {
            answerExist = true;
            // parentMap[s] = 12345678;
            break;
        }

        neighbors = getNeighbors(state);
        // for(auto n : neighbors)
        //     cout << "tst nej = " << n << endl;

        // for (auto neighbor : neighbors)
        bool firstTime = true;
        // if(neighbors.size() <= 0)
        //     --depth;

        for (auto neighbor = neighbors.rbegin(); neighbor != neighbors.rend(); neighbor++)
        {
            // cout << "neigh = " << *neighbor << endl;
            // int xxx = *neighbor;
            if ((isInFrontier.find(*neighbor) == isInFrontier.end()) && (explored.find(*neighbor) == explored.end()))
            {
                if(firstTime)
                {
                    firstTime = false;
                    ++depth;
                    maxDepth = maxDepth > depth ? maxDepth : depth;
                }
                ++depthMap[depth];
                frontier.push_back(*neighbor);
                isInFrontier.emplace(*neighbor);
                // cout << "yes\n";
                parentMap[*neighbor] = state;
            }
        }

        if(firstTime && depthMap[depth] == 1) {
            --depth;
            --depthMap[depth];
        }
        // cout << "******************\n";
    }
    vector<int> path;
    state = 12345678;
    path.push_back(state);
    while(state != inState)
    {
        // cout << "parent = " << parentMap[state] << endl;
        path.push_back(parentMap[state]);
        state = parentMap[state];
    }
    // sort(path.rbegin(),path.rend());
    for(auto xx : path)
    {
        cout << xx << "<---" << endl;

    }
    cout << parentMap.size() << " " << path.size()<< " " << maxDepth;
    // for (auto mp : parentMap)
    // {
    //     cout << mp.first << "-->" << mp.second << endl;
    // }

    // cout << answerExist;
    return 0;
}