#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <tuple>
#include <queue>
#include <utility>
#include <emscripten.h>

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

string stringifyPath(vector<int> path)
{
    // don't touch this code please ;_;
    int indexZero, oldR, oldC, newR, newC;
    string newZero, direction, currentZero, stringPath = "";
    for (unsigned long long i = path.size() - 1; i >= 1; --i)
    {
        if ((path[i] / 100000000) == 0)
        {
            indexZero = 0;
            oldR = 0;
            oldC = 0;
        }
        else
        {
            indexZero = to_string(path[i]).find('0');
            oldR = indexZero / 3;
            oldC = indexZero % 3;
        }
        currentZero = to_string(indexZero);

        if ((path[i - 1] / 100000000) == 0)
        {
            indexZero = 0;
            newR = 0;
            newC = 0;
        }
        else
        {
            indexZero = to_string(path[i - 1]).find('0');
            newR = indexZero / 3;
            newC = indexZero % 3;
        }
        newZero = to_string(indexZero);

        if (oldR > newR)
            direction = "down";
        else if (oldR < newR)
            direction = "up";
        else if (oldC > newC)
            direction = "right";
        else if (oldC < newC)
            direction = "left";

        stringPath += newZero + "-" + direction + "-" + currentZero + ",";
    }
    return stringPath;
}

// A utility function to count inversions in given array 'arr[]'
int getInvCount(int state)
{
    // don't touch this code please ;_;
    string strState = to_string(state);
    if ((state / 100000000) == 0)
        strState.insert(0, "0");

    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i + 1; j < 9; j++)
            if ((strState[j] - 48) && (strState[i] - 48) && ((strState[i] - 48) > (strState[j] - 48)))
                inv_count++;

    return inv_count;
}

// This function returns true if given 8 puzzle is solvable.
bool isSolvable(int state)
{
    // don't touch this code please ;_;
    // Count inversions in given 8 puzzle
    int invCount = getInvCount(state);

    // return true if inversion count is even.
    return (invCount % 2 == 0);
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

// tuple<vector<int>, long long, long long> solveBFS(int initialState)
// {
//     vector<int> finalPath;

//     unordered_map<int, int> parentMap; // bec insertion is O(1)
//     vector<int> frontier;
//     set<int> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
//     set<int> isInFrontier;
//     vector<int> neighbors;
//     int state;
//     long long expandedCount = 0;

//     frontier.push_back(initialState);
//     parentMap[initialState] = initialState;
//     isInFrontier.emplace(initialState);

//     while (!frontier.empty())
//     {
//         state = frontier[0];
//         frontier.erase(frontier.begin());
//         isInFrontier.emplace(state);
//         explored.emplace(state);
//         ++expandedCount;

//         if (state == 12345678)
//             break;

//         neighbors = getNeighbors(state);

//         for (auto neighbor : neighbors)
//         {
//             if ((isInFrontier.find(neighbor) == isInFrontier.end()) && (explored.find(neighbor) == explored.end()))
//             {
//                 frontier.push_back(neighbor);
//                 isInFrontier.emplace(neighbor);
//                 parentMap[neighbor] = state;
//             }
//         }
//     }

//     state = 12345678;
//     finalPath.push_back(state);
//     while (state != initialState)
//     {
//         finalPath.push_back(parentMap[state]);
//         state = parentMap[state];
//     }

//     tuple<vector<int>, long long, long long> result;
//     result = make_tuple(finalPath, expandedCount, finalPath.size());

//     return result;
// }

// tuple<vector<int>, long long, long long> solveDFS(int initialState)
// {
//     vector<int> finalPath;

//     unordered_map<int, int> parentMap; // bec insertion is O(1)
//     vector<int> frontier;
//     set<int> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
//     set<int> isInFrontier;
//     vector<int> neighbors;
//     int state;
//     long long expandedCount = 0, depth = 0, maxDepth = 0;

//     frontier.push_back(initialState);
//     parentMap[initialState] = initialState;
//     isInFrontier.emplace(initialState);

//     while (!frontier.empty())
//     {
//         state = frontier.back();
//         frontier.pop_back();
//         isInFrontier.emplace(state);
//         explored.emplace(state);
//         ++expandedCount;

//         if (state == 12345678)
//             break;

//         neighbors = getNeighbors(state);

//         bool neighborIsInserted = false;

//         for (auto neighbor = neighbors.rbegin(); neighbor != neighbors.rend(); neighbor++)
//         {
//             if ((isInFrontier.find(*neighbor) == isInFrontier.end()) && (explored.find(*neighbor) == explored.end()))
//             {
//                 if (!neighborIsInserted)
//                 {
//                     neighborIsInserted = true;
//                     ++depth;
//                     maxDepth = maxDepth > depth ? maxDepth : depth;
//                 }
//                 frontier.push_back(*neighbor);
//                 isInFrontier.emplace(*neighbor);
//                 parentMap[*neighbor] = state;
//             }
//         }
//         if (neighbors.size() <= 0)
//             --depth;
//     }

//     state = 12345678;
//     finalPath.push_back(state);
//     while (state != initialState)
//     {
//         finalPath.push_back(parentMap[state]);
//         state = parentMap[state];
//     }

//     tuple<vector<int>, long long, long long> result;
//     result = make_tuple(finalPath, expandedCount, finalPath.size());

//     return finalPath;
// }

vector<int> solveAStar(int initialState, int type)
{
    vector<int> finalPath;
    // code here
    // type = 0 ==> manhattan
    // type = 1 ==> euclidean

    unordered_map<int, int> parentMap; // bec insertion is O(1)
    unordered_map<int, int> costMap;   // bec insertion is O(1)
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

        if (explored.find(state) != explored.end())
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

    return finalPath;
}

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void solve(int initialState, int algorithmType)
    {
        // don't touch this code please ;_;
        string result = "";
        vector<int> path;
        bool isInitialStateSolvable = isSolvable(initialState);

        if (isInitialStateSolvable)
        {
            switch (algorithmType)
            {
            case 1:
                // path = solveBFS(initialState);
                break;
            case 2:
                // path = solveDFS(initialState);
                break;
            case 3:
                path = solveAStar(initialState, 0);
                break;
            case 4:
                path = solveAStar(initialState, 1);
                break;
            default:
                path = solveAStar(initialState, 1);
                break;
            }
            // The following three lines are for testing only.
            // Once you have a ready algorithm that return vector of string in path, delete them.
            // path.push_back(125340678);
            // path.push_back(120345678);
            // path.push_back(102345678);
            // path.push_back(12345678);
            // path.push_back(125348670);
            // path.push_back(125340678);
            // path.push_back(120345678);
            // path.push_back(102345678);
            // path.push_back(12345678);

            result = stringifyPath(path);
        }
        else
        {
            result = "unsolvable";
        }
        string script = "SolutionPanel('" + result + "')";
        const char *Schar = script.c_str();
        emscripten_run_script(Schar);
    }
}