#include <iostream>
#include <vector>
using namespace std;

struct edge{ int to,cap,cost,rev; };
static const int MAX = 100000;
static const int INF = 1e+9 + 7;
int V;
vector<edge> graph[MAX];
int dist[MAX];
int prevv[MAX],preve[MAX];

void add_edge(int from,int to,int cap,int cost){
  graph[from].push_back((edge){ to,cap,cost,(int)graph[to].size() });
  graph[to].push_back((edge){ from,0,-cost,(int)graph[from].size()-1 });
}

int min_cost_flow(int s,int t,int f){
  int res = 0;
  while(f > 0){
    fill(dist,dist + V,INF);
    dist[s] = 0;
    bool update = true;
    while(update){
      update = false;
      for(int v = 0;v < V;v++){
        if(dist[v] == INF)continue;
        for(int i = 0;i < graph[v].size();i++){
          edge &e = graph[v][i];
          if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
            dist[e.to] = dist[v] + e.cost;
            prevv[e.to] = v;
            preve[e.to] = i;
            update = true;
          }
        }
      }
    }
    if(dist[t] == INF)return -1;
    int d = f;
    for(int v = t;v != s;v = prevv[v]){
      d = min(d,graph[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += d * dist[t];
    for(int v = t;v != s;v = prevv[v]){
      edge &e = graph[prevv[v]][preve[v]];
      e.cap -= d;
      graph[v][e.rev].cap += d;
    }
  }
  return res;
}

int main(){
  return 0;
}
