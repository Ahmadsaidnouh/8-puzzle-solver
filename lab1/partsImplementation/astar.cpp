#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <utility>

using namespace std;
typedef pair<float, int> pi;

float hero(int state, int type)
{
    vector<pair<int, int>> indexes = {
        {0, 1},
        {0, 2},
        {1, 0},
        {1, 1},
        {1, 2},
        {2, 0},
        {2, 1},
        {2, 2}};
    // for (auto x : indexes)
    //     cout << x.first << " " << x.second << endl;

    string strState = to_string(state);
    // int i = 0;
    if (strState.size() == 8)
    {
        // i = 1;
        strState.insert(0, "0");
    }
    int r1, c1, r2, c2;
    float temp, heuristics = 0;
    for (int i = 0; i < 9; i++)
    {
        if (strState[i] == '0')
            continue;
        r1 = i / 3;
        c1 = i % 3;
        r2 = indexes[strState[i] - 48 - 1].first;
        c2 = indexes[strState[i] - 48 - 1].second;

        if (type == 0)
        {
            temp = abs(r1 - r2) + abs(c1 - c2);
        }
        else
        {
            temp = sqrt(abs(r1 - r2) * abs(r1 - r2) + abs(c1 - c2) * abs(c1 - c2));
        }

        heuristics += temp;

        // cout << temp << " " << heuristics << endl;
    }

    // if (type == 0) {
    //     if((state))
    // }
    return heuristics;
}


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
    int initialState;
    int type;
    cin >> initialState >> type;

    vector<int> finalPath;

    unordered_map<int, int> parentMap; // bec insertion is O(1)
    unordered_map<int, int> costMap;   // bec insertion is O(1)
    // vector<int> frontier;
    priority_queue<pi, vector<pi>, greater<pi>> frontier;
    set<int> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
    set<int> isInFrontier;
    vector<int> neighbors;
    int state;
    float cost;
    long long expandedCount = 0;

    frontier.push(make_pair(hero(initialState, type), initialState));
    parentMap[initialState] = initialState;
    isInFrontier.emplace(initialState);

    while (!frontier.empty())
    {
        cost = frontier.top().first;
        state = frontier.top().second;
        frontier.pop();

        if(explored.find(state) != explored.end())
            continue;

        isInFrontier.emplace(state);
        explored.emplace(state);
        ++expandedCount;

        if (state == 12345678)
            break;

        neighbors = getNeighbors(state);

        for (auto neighbor : neighbors)
        {
            if ((isInFrontier.find(neighbor) == isInFrontier.end()) && (explored.find(neighbor) == explored.end()))
            {
                int tot = 1 + cost + hero(neighbor, type);
                frontier.push(make_pair(tot, neighbor));
                costMap[neighbor] = tot;
                isInFrontier.emplace(neighbor);
                parentMap[neighbor] = state;
            }
            else if ((explored.find(neighbor) == explored.end()))
            {
                int tot = 1 + cost + hero(neighbor, type);
                if (tot < costMap[neighbor])
                {
                    frontier.push(make_pair(tot, neighbor));
                    costMap[neighbor] = tot;
                    parentMap[neighbor] = state;
                }
            }
        }
    }

    state = 12345678;
    finalPath.push_back(state);
    while (state != initialState)
    {
        finalPath.push_back(parentMap[state]);
        state = parentMap[state];
    }
    for(auto xx : finalPath)
    {
        cout << xx << "<---" << endl;

    }


    // tuple<vector<int>, long long, long long> result;
    // result = make_tuple(finalPath, expandedCount, finalPath.size());
    // hero(inState,1);

    // unordered_map<int, int> parentMap; // bec insertion is O(1)
    // vector<int> frontier;
    // map<int, bool> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
    // map<int, bool> isInFrontier;
    // vector<int> neighbors;
    // int state;
    // int depth = 0, maxDepth = 0;
    // // bool answerExist = false;

    // frontier.push_back(inState);
    // parentMap[inState] = inState;
    // isInFrontier[inState] = true;

    // while (!frontier.empty())
    // {
    //     state = frontier[0];
    //     frontier.erase(frontier.begin());
    //     isInFrontier[state] = false;
    //     // cout << "s = " << state << endl;
    //     explored[state] = true;

    //     if (state == 12345678)
    //     {
    //         // answerExist = true;
    //         // parentMap[s] = 12345678;
    //         break;
    //     }

    //     neighbors = getNeighbors(state);

    //     bool firstTime = true;
    //     if(neighbors.size() <= 0)
    //         --depth;

    //     for (auto neighbor : neighbors)
    //     {
    //         // cout << "neigh = " << neighbor << endl;

    //         if ((isInFrontier.find(neighbor) == isInFrontier.end()) && (explored.find(neighbor) == explored.end()))
    //         {
    //             if(firstTime)
    //             {
    //                 firstTime = false;
    //                 ++depth;
    //                 maxDepth = maxDepth > depth ? maxDepth : depth;
    //             }
    //             frontier.push_back(neighbor);
    //             isInFrontier[neighbor] = true;
    //             // cout << "yes\n";
    //             parentMap[neighbor] = state;
    //         }
    //         // try
    //         // {
    //         //     explored.at(neighbor);
    //         // }
    //         // catch (const std::exception &e)
    //         // {
    //         //     try
    //         //     {
    //         //         inFrontier.at(neighbor);
    //         //         if (!inFrontier[neighbor])
    //         //         {
    //         //             frontier.push_back(neighbor);
    //         //             inFrontier[neighbor] = true;

    //         //             parentMap[neighbor] = s;
    //         //         }
    //         //     }
    //         //     catch (const std::exception &e)
    //         //     {

    //         //         frontier.push_back(neighbor);
    //         //         inFrontier[neighbor] = true;

    //         //         parentMap[neighbor] = s;
    //         //     }
    //         // }
    //     }
    //     // cout << "******************\n";
    // }
    // vector<int> path;
    // state = 12345678;
    // path.push_back(state);
    // while(state != inState)
    // {
    //     // cout << "parent = " << parentMap[state] << endl;
    //     path.push_back(parentMap[state]);
    //     state = parentMap[state];
    // }
    // // sort(path.rbegin(),path.rend());
    // for(auto xx : path)
    // {
    //     cout << xx << "<---" << endl;

    // }
    // cout << parentMap.size() << " " << path.size() << " " << maxDepth;
    // // for (auto mp : parentMap)
    // // {
    // //     cout << mp.first << "-->" << mp.second << endl;
    // // }

    // // cout << answerExist;
    return 0;
}