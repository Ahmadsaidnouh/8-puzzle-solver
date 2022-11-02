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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// start utility functions////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string stringifyPath(tuple<vector<int>, long long, long long> result)
{
    // don't touch this code please ;_;

    vector<int> path = get<0>(result);
    long long expandedCount = get<1>(result);
    long long maxDepth = get<2>(result);

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

    string response = stringPath + ";" + to_string(expandedCount) + ";" + to_string(maxDepth);
    
    return response;
}

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

    string strState = to_string(state);
    
    if (strState.size() == 8)
        strState.insert(0, "0");

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
            temp = abs(r1 - r2) + abs(c1 - c2);
        else
            temp = sqrt(abs(r1 - r2) * abs(r1 - r2) + abs(c1 - c2) * abs(c1 - c2));

        heuristics += temp;
    }

    return heuristics;
}

int getInvCount(int state)
{
    // A utility function to count inversions in given array 'arr[]'
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

bool isSolvable(int state)
{
    // This function returns true if given 8 puzzle is solvable.
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// end utility functions//////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// start states solving functions/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
tuple<vector<int>, long long, long long> solveBFS(int initialState)
{
    vector<int> finalPath;

    unordered_map<int, int> parentMap; // bec insertion is O(1)
    vector<int> frontier;
    set<int> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
    set<int> isInFrontier;
    vector<int> neighbors;
    int state;
    // long long expandedCount = 0;

    frontier.push_back(initialState);
    parentMap[initialState] = initialState;
    isInFrontier.emplace(initialState);

    while (!frontier.empty())
    {
        state = frontier[0];
        frontier.erase(frontier.begin());
        isInFrontier.emplace(state);
        explored.emplace(state);
        // ++expandedCount;

        if (state == 12345678)
            break;

        neighbors = getNeighbors(state);

        for (auto neighbor : neighbors)
        {
            if ((isInFrontier.find(neighbor) == isInFrontier.end()) && (explored.find(neighbor) == explored.end()))
            {
                frontier.push_back(neighbor);
                isInFrontier.emplace(neighbor);
                parentMap[neighbor] = state;
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

    tuple<vector<int>, long long, long long> result;
    result = make_tuple(finalPath, explored.size(), finalPath.size() - 1);

    return result;
}

tuple<vector<int>, long long, long long> solveDFS(int initialState)
{
    vector<int> finalPath;

    // unordered_map<int, int> parentMap; // bec insertion is O(1)
    unordered_map<int, pair<int, long long>> parentMap; // bec insertion is O(1)
    vector<int> frontier;
    set<int> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
    set<int> isInFrontier;
    vector<int> neighbors;
    int state;
    // long long expandedCount = 0;
    // long long depth = 0, maxDepth = 0;
    long long maxDepth = 0;

    frontier.push_back(initialState);
    parentMap[initialState] = make_pair(initialState, 0) ;
    isInFrontier.emplace(initialState);

    while (!frontier.empty())
    {
        state = frontier.back();
        frontier.pop_back();
        isInFrontier.emplace(state);
        explored.emplace(state);
        // ++expandedCount;

        maxDepth = maxDepth > parentMap[state].second ? maxDepth : parentMap[state].second;

        if (state == 12345678)
            break;

        neighbors = getNeighbors(state);

        // bool neighborIsInserted = false;

        // if(neighbors.size() == 0)
        // {
        //     continue;
        // }

        for (auto neighbor = neighbors.rbegin(); neighbor != neighbors.rend(); neighbor++)
        {
            if ((isInFrontier.find(*neighbor) == isInFrontier.end()) && (explored.find(*neighbor) == explored.end()))
            {
                // if (!neighborIsInserted)
                // {
                //     neighborIsInserted = true;
                //     ++depth;
                //     maxDepth = maxDepth > depth ? maxDepth : depth;
                // }
                frontier.push_back(*neighbor);
                isInFrontier.emplace(*neighbor);
                parentMap[*neighbor] = make_pair(state,parentMap[state].second+1);
            }
        }
        // if (neighbors.size() <= 0)
        //     --depth;
    }

    state = 12345678;
    finalPath.push_back(state);
    while (state != initialState)
    {
        finalPath.push_back(parentMap[state].first);
        state = parentMap[state].first;
    }

    tuple<vector<int>, long long, long long> result;
    // result = make_tuple(finalPath, explored.size(), finalPath.size());
    result = make_tuple(finalPath, explored.size(), maxDepth);

    return result;
}

tuple<vector<int>, long long, long long> solveAStar(int initialState, int type)
{
    vector<int> finalPath;
    // code here
    // type = 0 ==> manhattan
    // type = 1 ==> euclidean

    unordered_map<int, pair<int, long long>> parentMap; // bec insertion is O(1)
    unordered_map<int, int> costMap;   // bec insertion is O(1)
    priority_queue<pi, vector<pi>, greater<pi>> frontier;
    set<int> explored; // bec find() is O(lg(n)) in worst case. unorderd is O(n) in worst case.
    set<int> isInFrontier;
    vector<int> neighbors;
    int state, newF;
    float f, g;
    // long long expandedCount = 0;
    long long maxDepth = 0;

    frontier.push(make_pair(hero(initialState, type), initialState));
    parentMap[initialState] = make_pair(initialState, 0);
    isInFrontier.emplace(initialState);

    while (!frontier.empty())
    {
        f = frontier.top().first;
        state = frontier.top().second;
        frontier.pop();
        g = f - hero(state, type);

        if (explored.find(state) != explored.end())
            continue;

        isInFrontier.emplace(state);
        explored.emplace(state);
        // ++expandedCount;

        maxDepth = maxDepth > parentMap[state].second ? maxDepth : parentMap[state].second;

        if (state == 12345678)
            break;

        neighbors = getNeighbors(state);



        for (auto neighbor : neighbors)
        {
            if ((isInFrontier.find(neighbor) == isInFrontier.end()) && (explored.find(neighbor) == explored.end()))
            {
                newF = 1 + g + hero(neighbor, type);
                frontier.push(make_pair(newF, neighbor));
                costMap[neighbor] = newF;
                isInFrontier.emplace(neighbor);
                parentMap[neighbor] = make_pair(state,parentMap[state].second+1);
            }
            else if ((explored.find(neighbor) == explored.end()))
            {
                newF = 1 + g + hero(neighbor, type);
                if (newF < costMap[neighbor])
                {
                    frontier.push(make_pair(newF, neighbor));
                    costMap[neighbor] = newF;
                    parentMap[neighbor] = make_pair(state,parentMap[state].second+1);
                }
            }
        }
    }

    state = 12345678;
    finalPath.push_back(state);
    while (state != initialState)
    {
        finalPath.push_back(parentMap[state].first);
        state = parentMap[state].first;
    }

    tuple<vector<int>, long long, long long> result;
    // result = make_tuple(finalPath, expandedCount, finalPath.size());
    result = make_tuple(finalPath, explored.size(), maxDepth);

    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// end states solving functions///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// start main driver code/////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void solve(int initialState, int algorithmType)
    {
        // don't touch this code please ;_;
        string result = "";
        tuple<vector<int>, long long, long long> path;
        bool isInitialStateSolvable = isSolvable(initialState);

        if (isInitialStateSolvable)
        {
            switch (algorithmType)
            {
            case 1:
                path = solveBFS(initialState);
                break;
            case 2:
                path = solveDFS(initialState);
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// end main driver code///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////