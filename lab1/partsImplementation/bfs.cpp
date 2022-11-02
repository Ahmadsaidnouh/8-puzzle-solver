#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <map>

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
    map<int, bool> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
    map<int, bool> isInFrontier;
    vector<int> neighbors;
    int state;
    int depth = 0, maxDepth = 0;
    // bool answerExist = false;

    frontier.push_back(inState);
    parentMap[inState] = inState;
    isInFrontier[inState] = true;

    while (!frontier.empty())
    {
        state = frontier[0];
        frontier.erase(frontier.begin());
        isInFrontier[state] = false;
        // cout << "s = " << state << endl;
        explored[state] = true;

        if (state == 12345678)
        {
            // answerExist = true;
            // parentMap[s] = 12345678;
            break;
        }

        neighbors = getNeighbors(state);

        bool firstTime = true;
        if(neighbors.size() <= 0)
            --depth;

        for (auto neighbor : neighbors)
        {
            // cout << "neigh = " << neighbor << endl;

            if ((isInFrontier.find(neighbor) == isInFrontier.end()) && (explored.find(neighbor) == explored.end()))
            {
                if(firstTime)
                {
                    firstTime = false;
                    ++depth;
                    maxDepth = maxDepth > depth ? maxDepth : depth;
                }
                frontier.push_back(neighbor);
                isInFrontier[neighbor] = true;
                // cout << "yes\n";
                parentMap[neighbor] = state;
            }
            // try
            // {
            //     explored.at(neighbor);
            // }
            // catch (const std::exception &e)
            // {
            //     try
            //     {
            //         inFrontier.at(neighbor);
            //         if (!inFrontier[neighbor])
            //         {
            //             frontier.push_back(neighbor);
            //             inFrontier[neighbor] = true;

            //             parentMap[neighbor] = s;
            //         }
            //     }
            //     catch (const std::exception &e)
            //     {

            //         frontier.push_back(neighbor);
            //         inFrontier[neighbor] = true;

            //         parentMap[neighbor] = s;
            //     }
            // }
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
    cout << parentMap.size() << " " << path.size() << " " << maxDepth;
    // for (auto mp : parentMap)
    // {
    //     cout << mp.first << "-->" << mp.second << endl;
    // }

    // cout << answerExist;
    return 0;
}