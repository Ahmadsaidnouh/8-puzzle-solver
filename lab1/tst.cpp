#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

vector<int> getNeighbors(int state)
{
    // don't touch this code please ;_;
    cout << 1 << endl;
    vector<int> neighbors;
    string strState = to_string(state);
    cout << "STATE = " << strState << endl;
    cout << 2 << endl;

    if ((state / 100000000) == 0)
    {
        // indexZero = 0;
        // rowZero = 0;
        // columnZero = 0;
        // strState = to_string(state);
        strState.insert(0, "0");
    }
    else
    {
        // strState = to_string(state);

        // indexZero = to_string(state).find('0');
        // rowZero = indexZero / 3;
        // columnZero = indexZero % 3;
    }
    cout << 3 << endl;
    int indexZero = strState.find('0');
    int rowZero = indexZero / 3;
    int columnZero = indexZero % 3;

    int rowTmp, colTmp, newIndexZero;
    char temp;
    if ((state / 100000000) != 0)
    {
        // indexZero = 0;
        // rowZero = 0;
        // columnZero = 0;
        // strState = to_string(state);
        // strState.insert(0, "0");
    }
        // strState.erase(indexZero,1);
    // cout << "STATE = " << strState << endl;
    // cout << 4 << endl;
    // cout << "row = " << rowZero << " column = " << columnZero << endl;

    string sTemp = "";
    rowTmp = rowZero - 1;
    colTmp = columnZero;
    if ((rowTmp <= 2) && (rowTmp >= 0) && (colTmp <= 2) && (colTmp >= 0))
    {
        sTemp = strState;
        // cout << "stemp = " << sTemp << " strState = " << strState << endl;
        newIndexZero = rowTmp * 3 + colTmp;
        // cout << "new = " << newIndexZero << endl;
        sTemp[indexZero] = sTemp[newIndexZero];
        sTemp[newIndexZero] = '0';
        // sTemp.insert(newIndexZero, "0");
        neighbors.push_back(stoi(sTemp));
    }
    // cout << 5 << endl;

    sTemp = "";
    rowTmp = rowZero + 1;
    colTmp = columnZero;
    if ((rowTmp <= 2) && (rowTmp >= 0) && (colTmp <= 2) && (colTmp >= 0))
    {
        sTemp = strState;
        // cout << "stemp = " << sTemp << " strState = " << strState << endl;
        newIndexZero = rowTmp * 3 + colTmp;
        // cout << "new = " << newIndexZero << endl;
        sTemp[indexZero] = sTemp[newIndexZero];
        sTemp[newIndexZero] = '0';
        // sTemp.insert(newIndexZero, "0");
        neighbors.push_back(stoi(sTemp));
    }
    // cout << 6 << endl;

    sTemp = "";
    rowTmp = rowZero;
    colTmp = columnZero - 1;
    if ((rowTmp <= 2) && (rowTmp >= 0) && (colTmp <= 2) && (colTmp >= 0))
    {
        sTemp = strState;
        // cout << "stemp = " << sTemp << " strState = " << strState << endl;
        newIndexZero = rowTmp * 3 + colTmp;
        // cout << "new = " << newIndexZero << endl;
        sTemp[indexZero] = sTemp[newIndexZero];
        sTemp[newIndexZero] = '0';
        // sTemp.insert(newIndexZero, "0");
        neighbors.push_back(stoi(sTemp));
    }
    // cout << 7 << endl;

    sTemp = "";
    rowTmp = rowZero;
    colTmp = columnZero + 1;
    if ((rowTmp <= 2) && (rowTmp >= 0) && (colTmp <= 2) && (colTmp >= 0))
    {
        sTemp = strState;
        // cout << "stemp = " << sTemp << " strState = " << strState << endl;
        newIndexZero = rowTmp * 3 + colTmp;
        // cout << "new = " << newIndexZero << endl;
        sTemp[indexZero] = sTemp[newIndexZero];
        sTemp[newIndexZero] = '0';
        // sTemp.insert(newIndexZero, "0");
        neighbors.push_back(stoi(sTemp));
    }

    return neighbors;
}

int main()
{
    // string st = "hello";
    // st.insert(3, "0");
    // cout << st;
    int n;
    for (int i = 0; i < 9; i++)
    {
        
    
    cin >> n;
    vector<int> v = getNeighbors(n);
    for (auto vv : v)
    {
        cout << vv << endl;
    }
    cout << "s*********\n";
    }
    return 0;
}