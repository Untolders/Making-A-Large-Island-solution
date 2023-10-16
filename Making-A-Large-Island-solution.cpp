***************************************************************************************  Question  *********************************************************************************************

You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1. A group of connected 1s forms an island. Two 1s are connected if they share one of their sides with each other.

Return the size of the largest island in the grid after applying this operation.

Example 1:

Input: 
grid = [[1,0],[0,1]]
Output:
3
Explanation:
Change any one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:

Input: 
grid = [[1,1],[1,0]]
Output:
4
Explanation:
Change the only 0 to 1 and make the island bigger, then we get an island with area = 4.
Example 3:

Input: 
grid = [[1,1],[1,1]]
Output:
4
Explanation:
Can't change any 0 to 1, only one island possible with area = 4.
Your Task:

You don't have to read input or print anything. You have to complete the functions largestIsland(), which takes binary matrix as input and returns an integer denoting the size of the largest island in grid after applying the operation.

Constraints:

1 <= n <= 500
0 <= grid[i][j] <= 1 (grid[i][j] ∈ {0, 1} and 0<=i,j<n)




****************************************************************************************  Answer  ********************************************************************************************
//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
//User function Template for C++
class Solution
{
public:
    void calculateisland(vector<vector<int>>& grid, vector<vector<int>>& divideparts, int i, int j, int actualisland, unordered_map<int, int>& islandsizes, int& maxsize){
    queue<pair<int, int>> q;
    q.push({i, j});
    int size=0;
    while(!q.empty()){
        pair<int, int> p=q.front();
        q.pop();
        if (p.first<0 || p.first>=grid.size() || p.second<0 || p.second>=grid[0].size() || divideparts[p.first][p.second]!=0 || grid[p.first][p.second]==0){
            continue;
        }
        divideparts[p.first][p.second]=actualisland;
        size++;
        q.push({p.first+1, p.second});
        q.push({p.first-1, p.second});
        q.push({p.first, p.second+1});
        q.push({p.first, p.second-1});
    }
    islandsizes[actualisland]=size;
    maxsize=max(maxsize, size);
}

int largestIsland(vector<vector<int>>& grid) {
    int maxsize=0;
    int actualisland=1;
    unordered_map<int, int> islandsizes;
    vector<vector<int>> divideparts(grid.size(), vector<int>(grid[0].size(), 0));
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if (divideparts[i][j]==0 && grid[i][j]==1){
                calculateisland(grid, divideparts, i, j, actualisland, islandsizes, maxsize);
                actualisland++;
            }
        }
    }
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(grid[i][j]==0){
                int possiblesize=1;
                set<int> s;
                if(i-1>=0 && divideparts[i-1][j]!=0 && s.find(divideparts[i-1][j])==s.end()){
                    possiblesize+=islandsizes[divideparts[i-1][j]];
                    s.insert(divideparts[i-1][j]);
                }
                if(i+1<grid.size() && divideparts[i+1][j]!=0 && s.find(divideparts[i+1][j])==s.end()){
                    possiblesize+=islandsizes[divideparts[i+1][j]];
                    s.insert(divideparts[i+1][j]);
                }
                if(j-1>=0 && divideparts[i][j-1]!=0 && s.find(divideparts[i][j-1])==s.end()){
                    possiblesize+=islandsizes[divideparts[i][j-1]];
                    s.insert(divideparts[i][j-1]);
                }
                if(j+1<grid[0].size() && divideparts[i][j+1]!=0 && s.find(divideparts[i][j+1])==s.end()){
                    possiblesize+=islandsizes[divideparts[i][j+1]];
                    s.insert(divideparts[i][j+1]);
                }
                maxsize=max(maxsize, possiblesize);
            }
        }
    }
    return maxsize;
}
};

//{ Driver Code Starts.

int main(){
    int t;
    cin >> t;
    while(t--){

        int n;
        cin>>n;
        vector<vector<int>>grid(n,vector<int>(n));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin>>grid[i][j];
        Solution ob;
        cout<<ob.largestIsland(grid)<<endl;
    }
    return 0;
}

// } Driver Code Ends

