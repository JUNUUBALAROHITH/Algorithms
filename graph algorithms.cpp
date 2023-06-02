#include <bits/stdc++.h>
using namespace std;
#define int long long
int t;
const int MAX = 1e9 + 7;

// declaration of priority queue with ascending order 
priority_queue<int, vector<int>, greater<int>> q;


// null graph --> no edges between the vertices
// trivia graph --> having only one vertex
// degree of self loop=2
// degree of node in directed graph = indegree+outdegree

vector< vector< int> > adj;
vector<bool> vis;
vector<int> col; // for coloured labels problem and also for further use in cycle detection...
vector<int> in,out;
// adj.resize(v)--> in solve() function for each test case
// vis.resize(v,0)--> in solve() function for each testcase
// resize() function is more useful to make global vectors


// breath first search
int level[n];
vector<int> bfsOfGraph(int V, vector<int> adj[]){
    vector<bool> visited(V, false);
    int s = 0;
    visited[s] = true; 
    vector<int> res;
    queue<int> q;
    q.push(s);
    level[s]=0;
    while (!q.empty()) {
        int t = q.front();
        res.push_back(t);
        q.pop();
        for(int v : adj[t])
            if(!visited[v]){ 
                visited[v] = true;
                level[v]=level[t]+1;  //stores distance from src node
                q.push(v);
            }
    }
    return res;
}

// If there are multiple sources, we will put the all source
// vertices to the queue at first rather than a single
// vertex which was in case of standard BFS.
//  connected graph with n nodes and n-1 edges is a tree
// connected graph with n node and n edges is a graph with exactly one cycle
// each node has single parent in tree

// 0-1 bfs
void bfs(int startX, int startY, int r, int c){
    dis[startX][startY] = 0;
    deque< pair<int, int> > q;
    pair<int, int> p;
    q.push_front(make_pair(startX, startY));
    while(!q.empty()){
        p = q.front();
        q.pop_front();
        int x = p.first;
        int y = p.second;
        int a[] = {0, -1, 0, 1};
        int b[] = {-1, 0, 1, 0};
        for(int i=0;i<4;i++){
            int tmpX = x + a[i];
            int tmpY = y + b[i];
            if(in_range(tmpX, tmpY, r, c)){
                if(mat[tmpX][tmpY] == mat[x][y] && dis[tmpX][tmpY] > dis[x][y]){
                    q.push_front(make_pair(tmpX,tmpY));
                    dis[tmpX][tmpY] = dis[x][y];
                }
                else if(mat[tmpX][tmpY] !=mat[x][y]){
                    if(dis[tmpX][tmpY] > dis[x][y] + 1){
                        q.push_back(make_pair(tmpX,tmpY));
                        dis[tmpX][tmpY] = dis[x][y] + 1;
                    }
                }
            }
        }
    }
}


void dfs(int v){  // O(V+E)
    vis[v]=1;
    cout<<v<<"->";
    for(int child : adj[v]){
        if(vis[child]==0) dfs(child);
    }
}

int cc(){
    int c=0;
    for(int i=1;i<=n;i++){
        if(vis[i]==0){
            c++;
            dfs(i);
        }
    }
    return c;
}

// Bipartite graph
// each vertex belongs to exactly one of two disjoin sets
// each edge connects vertices of 2 different sets

bool bipartite(int v,int c){
    vis[v]=1;
    col[v]=c;
    for(int child:adj[v]){
        if(!vis[v]){
            if(bipartite(child,c^1)==false) return false;
        }
        else{
            if(col[v]==col[child]) return false;
        }
    }
    return true;
}

// if connected components=1 && e=v-1 --> tree topology

// cycle detection using dfs
bool cycleDetection(int node,int par){
    vis[node]=1;
    for(int child:adj[node]){
        if(vis[child]==0){
            if(cycleDetection(child,node)) return 1;
        }
        else{
            if(child!=par) return 1;
        }
    }
    return 0;
}

// in /out time implementation in dfs
int timer=1;
bool dfs(int v){
    vis[v]=1;
    in[v]=timer++;
    for(auto child:adj[v]){
        if(!vis[child]){
            dfs(child);
        }
    }
    out[v]=timer++;
}

// diameter of tree 
// naive approch : O(n^2)
// better approch:
// only 2 dfs runs
// take arbitary node as root ,run dfs find farthest node let it be x
// run dfs from x and find max distance from this node to any other node this distance is diameter
// implementation:
int ma = -1, maxNode;

void dfs(int v,int dis)
{
    vis[v] = 1;
    if (ma < dis)
    {
        ma = dis;
        maxNode = v;
    }
    for (auto i : adj[v])
    {
        if (!vis[i])
        {
            dfs(i, adj, vis, dis + 1);
        }
    }
}

// BRIDGE: A Bridge is an edge which when removed increases connected components
// Back edges can never be bridges
int timer;
// DFS based implementation to find bridge edges

void dfs(int node ,int par){
    vis[node]=1;
    in[node]=low[node]=timer;
    timer++;
    for(auto child:adj[node]){
        if(child==par) continue;
        if(vis[child]){
            // back edge
            low[node]=min(low[node],in[child]);
        }
        else{
            // forward edge
            dfs(child,node);
            if(low[child]>in[node]){
                cout<<node<<" "<<child<<" is a bridge\n";
                low[node]=min(low[node],low[child]);
            }
        }
    }
}

// ARTICULATION POINT: vertex which when removed increases the no of connected components
// there exist articulation point without bridges
// end points of a bridge will be articulation point if that node has degree atleast 2

int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                IS_CUTPOINT(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        IS_CUTPOINT(v);
}

void find_cutpoints() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i);
    }
}

// Topological sort is not unique for same graph
// many valid are possible
// If there exist cycle in the graph then there is no topological sort exists
// Kahn`s algo:choose each time a vertex such that its indegree is zero and remove all its edges and continue same step
int in[v+1]; // to store in degree of each vertex
// for(int i=1;i<=e;i++){
//     cin>>x>>y;
//     adj[x].push_back(y);
//     in[y]++; // directed graph
// }
// TopoSort-I
vector<int> TopoSort(vector<vector<int>> &adj,int v){
    queue<int> q;
    vector<int> res; // to store result
    for(int i=1;i<=n;i++){
        if(in[i]==0) q.push(i);
    }
    while(!q.empty()){
        int cur=q.front();
        res.push_back(cur);
        q.pop();
        for(auto child: adj[cur]){
            in[child]--;
            if(in[child]==0) q.push(child);
        }
    }
    return res;
}

// TopoSort-II - Decreasing order of their finishing times
int n; // no. of nodes
vector<vector<int> > adj; // adjacency list
vector<bool> vis;
// initialise all values with false
stack<int> st;
void dfs(int node)
{
    vis[node]=true;
    for(auto child: adj[node])
    {
        if ( ! vis[child] )
        {
            dfs(child);
        }
    }
    st.push(node);
    // push to stack when finished
}

void solve()
{
    int v,e;
    cin >> v>>e;
    vector<vector<int>> adj(v + 1);
    int x, y;
    for (int i = 0; i < e; i++)
    {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for(int i=0;i<=v;i++){
        sort(adj[i].begin(),adj[i].end())
    }
    vector<bool> vis(n + 1, 0);
    dfs(1, adj, vis, 0);
    for (int i = 1; i < n + 1; i++)
        vis[i] = 0;
    ma = -1;
    dfs(maxNode, adj, vis, 0);
    cout << ma << '\n';
}

// counting subtrees of all nodes
int dfs(int node){
    vis[node]=1;
    int cur_size=1;
    for(auto child:adj[node]){
        if(vis[child]==0) cur_size+=dfs(child);
    }
    subSize[node]=cur_size;
    return cur_size;
}

// grids
// cell-->node
// side-->edge

// Applying DFS on 2D grid

bool isValid(int x,int y){
    if(x<1 || y<1 || x>n || y>m) return false;
    return true;
}

int dx[4]={0,0,-1,1}
int dy[4]={1,-1,0,0};
void dfs(int x,int y){
    vis[x][y]=1;
    if(isValid(x-1,y)) dfs(x-1,y);
    if(isValid(x,y-1)) dfs(x,y-1);
    if(isValid(x+1,y)) dfs(x+1,y);
    if(isValid(x,y+1)) dfs(x,y+1);
    /*...........or.............*/
    for(int i=0;i<4;i++){
        if(isValid(x+dx[i],y+dy[i])){
            dfs(x+dx[i],y+dy[i]);
        }
    }
}

// no of connected components
int cnt=0;
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        if(v[i][j]==1 && vis[i][j]==0){
            cnt++;
            dfs(i,j);
        }
    }
}

// Applying BFS on 2D grids
// case1:edges-->common sides only
// case2:edges-->common sides+common corners

void BFS(int srcX,int srcY){
    queue<pair<int,int>> q;
    q.push({srcX,srcY});
    dist[srcX][srcY]=0;
    vis[srcX][srcY]=1;
    while(!q.empty()){
        int currX=q.front().first;
        int currY=q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            if(isValid(currX+dx[i],currY+dy[i])){
                int newX=currX+dx[i];
                int newY=currY+dy[i];
                dist[newX][newY]=dist[currX][currY]+1;
                vis[newX][newY]=1;
                q.push({newX,newY});
            }
        }
    }
}


// Storongly Connected Components
// for every pair of vertices there exist a path
// Transposed Graph: reversing direction of edges in directed graph
// Condensation graph:
// Each SCC acts as vertex in condensation graph
// Condensation graph doesnt contain any cycle
// if Ci ,Cj are SCC and there exists edge from Ci to Cj then out[Ci]>out[Cj]

// rotten orange problem:
int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, -1, 1, 0};

int orangesRotting(vector<vector<int>>& v) {
    int n=v.size();
    int m=v[0].size();
    queue<pair<int,int>> q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(v[i][j]==2) q.push({i,j});
        }
    }
    int ans=0;
    vector<vector<int>> vis(n,vector<int> (m,0));
    while(!q.empty()){
        ans++;
        int a=q.size();
        pair<int,int> p;
        for(int i=0;i<a;i++){
            p=q.front();
            q.pop();
            vis[p.first][p.second]=1;
            v[p.first][p.second]=2;
            for(int x=0;x<4;x++){
                int y=p.first+dx[x];
                int z=p.second+dy[x];
                if(y>=0&&z>=0&&y<n&&z<m){
                    if(vis[y][z]==0&&v[y][z]==1){
                        vis[y][z]=1;
                        q.push({y,z});
                    }
                }
            }
        }

        // queue<pair<int,int>> s=q;
        // cout<<s.size()<<"\n";
        // for(int i=0;i<q.size();i++){
        //     p=s.front();
        //     cout<<p.first<<" "<<p.second<<'\n';
        //     s.pop();
        // }
        // cout<<'\n';
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(v[i][j]==1){
                return -1;
            }
        }
    }
    return ans-1;
}

void solve()
{
    int n>>m;
    cin>>n>>m;
    int adj[n+1][m+1];
    for(int i=0;i<m;i++){  // adjacency matrix
        int u,v;
        cin>>u>>v;
        adj[u][v]=1;
        adj[v][u]=1;
    }

    for(int i=0;i<m;i++){  // adjacency list
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    } 
}

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
