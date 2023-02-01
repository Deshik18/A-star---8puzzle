#include<bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool costofempty=false;
bool monotone = true;
string goal;
char c='0';
map<string, int> visited;
map<string, int> dist;
int max_depth=0;


struct track{
    string prev;
    char move;
    string pre;
};
struct track node[1000000];
int node_idx=0;


int front;
int rear;
string state[1000000];
int key[1000000];
void enqueue(string s,int k){
    cout << "enqueue:" << s << " " << k << endl;
    front++;
    state[front]=s;
    key[front]=k;
}
string extractmin(){
    int shortidx;
    int min=INT_MAX;
    for(int i=rear+1;i<=front;i++){
        if(key[i]<min){
            min=key[i];
            shortidx=i;
        }
    }
    string temp=state[shortidx];
    for(int i=shortidx;i>rear;i--){
        state[i]=state[i-1];
        key[i]=key[i-1];
    }
    rear++;
    //cout << "deque:" << temp << endl;
    return temp;
}


int heuristic(string s,int hind){
    if(hind==1){
        return 0;
    }
    else if(hind==2){
        int m=0;
        for(int i=0;i<9;i++){
            if(s[i]!=goal[i]){
                if(costofempty){
                    m++;
                }
                else{
                    if(s[i]!=c){
                        m++;
                    }
                }   
            }
        }
        return m;
    }
    else if(hind==3){
        int m=0;
        char sarr[3][3],goalarr[3][3];
        int idx=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                sarr[i][j]=s[idx];
                goalarr[i][j]=goal[idx];
                idx++;
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                char alpha=sarr[i][j];
                for(int x=0;x<3;x++){
                    for(int y=0;y<3;y++){
                        if(alpha==goalarr[x][y]){
                            if(costofempty){
                                 m+=abs(x-i)+abs(y-j);
                                break;
                            }
                            else{
                                if(alpha!=c){
                                    m+=abs(x-i)+abs(y-j);
                                    break;
                                }
                            }    
                        }
                    }
                }
            }
        }
        return m;
    }
    else{
        int m=0;
        char sarr[3][3],goalarr[3][3];
        int idx=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                sarr[i][j]=s[idx];
                goalarr[i][j]=goal[idx];
                idx++;
            }
        }
        int clock_score=7;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                char alpha=sarr[i][j];
                for(int x=0;x<3;x++){
                    for(int y=0;y<3;y++){
                        if(alpha==goalarr[x][y]){
                            if(alpha!=c){
                                m+=abs(x-i)+abs(y-j);
                                break;
                            }
                        }
                    }
                }
            }
        }
        int c_score=1;
        if(sarr[1][1]==goalarr[1][1]){
            c_score=0;
        }
        string current_clock="";
        current_clock+=s[0];
        current_clock+=s[1];
        current_clock+=s[2];
        current_clock+=s[5];
        current_clock+=s[8];
        current_clock+=s[7];
        current_clock+=s[6];
        current_clock+=s[3];
        string goal_clock="";
        goal_clock+=goal[0];
        goal_clock+=goal[1];
        goal_clock+=goal[2];
        goal_clock+=goal[5];
        goal_clock+=goal[8];
        goal_clock+=goal[7];
        goal_clock+=goal[6];
        goal_clock+=goal[3];
        for(int i=0;i<7;i++){
            string che="";
            che+=current_clock[i];
            che+=current_clock[i+1];
            for(int j=0;j<8;j++){
                string chy="";
                if(j==7){
                    chy+=goal_clock[7];
                    chy+=goal_clock[0];
                }
                else{
                    chy+=goal_clock[j];
                    chy+=goal_clock[j+1];
                }
                if(che==chy){
                    clock_score--;
                    break;
                }
            }
        }
        return m+3*(c_score+2*clock_score);
    }
}


int discovery(){
    int i;
    for(i=0;i<node_idx;i++){
        if(node[i].pre==goal){
            return i;
        }
    }
}


void path(string source,int htype){
    vector<char> record;
    vector<string> nodegen;
    string present=goal;
    cout << "--------------------------" << endl;
    while(present!=source){
        for(int i=0;i<node_idx;i++){
            if(present==node[i].pre){
                record.push_back(node[i].move);
                cout << "heuristic of fut :" << heuristic(present,htype) << "\t";
                present = node[i].prev;
                cout << "heuristic of pre :" << heuristic(present,htype) << endl;
                break;
            }
        }
    }
    cout << "--------------------------" << endl;
    for(int i=record.size()-1;i>=0;i--){
        cout << record[i] << " ->";
    }
    cout << endl << endl;
    cout << "goal";
}

void astar(string source,int htype){
    front=-1;
    rear=-1;
    visited[source]=1;
    dist[source]=0;
    node[node_idx].prev="-1";
    node[node_idx].move='S';
    node[node_idx].pre=source;
    node_idx++;
    enqueue(source,(dist[source]+(heuristic(source,htype))));
    while(front!=rear){
        string u=extractmin();
        int s_heur=heuristic(u,htype);
        if(u==goal){
            cout << "Goal Found!!..." << endl;
            cout << "Nodes Explored :" << node_idx << endl;
            cout << "Goal Node Discoved number :" << discovery()+1 << endl;
            cout << "Depth of goal node:" << dist[goal] << endl;
            cout << "Max Depth: " << max_depth << endl;
            cout << "Path :";
            path(source,htype);
            cout << endl;
            return;
        }
        int brow,bcol;
        char sarr[3][3];
        int idx=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                sarr[i][j]=u[idx];
                idx++;
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(sarr[i][j]==c){
                    brow=i;
                    bcol=j;
                }
            }
        }
        if(brow!=0){
            sarr[brow][bcol]=sarr[brow-1][bcol];
            sarr[brow-1][bcol]=c;
            string nnode="";
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    nnode+=sarr[i][j];
                }
            }
            if(visited.find(nnode)==visited.end()){
                visited[nnode]=1;
                dist[nnode]=dist[u]+1;
                node[node_idx].prev=u;
                node[node_idx].move='U';
                node[node_idx].pre=nnode;
                node_idx++;
                if(heuristic(nnode,htype)>s_heur+1){
                    monotone = false;
                }
                enqueue(nnode,(dist[nnode]+heuristic(nnode,htype)));
            }
            sarr[brow-1][bcol]=sarr[brow][bcol];
            sarr[brow][bcol]=c;
        }
        if(brow!=2){
            sarr[brow][bcol]=sarr[brow+1][bcol];
            sarr[brow+1][bcol]=c;
            string nnode="";
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    nnode+=sarr[i][j];
                }
            }
            if(visited.find(nnode)==visited.end()){
                visited[nnode]=1;
                dist[nnode]=dist[u]+1;
                node[node_idx].prev=u;
                node[node_idx].move='D';
                node[node_idx].pre=nnode;
                node_idx++;
                if(heuristic(nnode,htype)>s_heur+1){
                    monotone = false;
                }
                enqueue(nnode,(dist[nnode]+heuristic(nnode,htype)));
            }
            sarr[brow+1][bcol]=sarr[brow][bcol];
            sarr[brow][bcol]=c;
        }
        if(bcol!=0){
            sarr[brow][bcol]=sarr[brow][bcol-1];
            sarr[brow][bcol-1]=c;
            string nnode="";
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    nnode+=sarr[i][j];
                }
            }
            if(visited.find(nnode)==visited.end()){
                visited[nnode]=1;
                dist[nnode]=dist[u]+1;
                node[node_idx].prev=u;
                node[node_idx].move='L';
                node[node_idx].pre=nnode;
                node_idx++;
                if(heuristic(nnode,htype)>s_heur+1){
                    monotone = false;
                }
                enqueue(nnode,(dist[nnode]+heuristic(nnode,htype)));
            }
            sarr[brow][bcol-1]=sarr[brow][bcol];
            sarr[brow][bcol]=c;
        }
        if(bcol!=2){
            sarr[brow][bcol]=sarr[brow][bcol+1];
            sarr[brow][bcol+1]=c;
            string nnode="";
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    nnode+=sarr[i][j];
                }
            }
            if(visited.find(nnode)==visited.end()){
                visited[nnode]=1;
                dist[nnode]=dist[u]+1;
                node[node_idx].prev=u;
                node[node_idx].move='R';
                node[node_idx].pre=nnode;
                node_idx++;
                if(heuristic(nnode,htype)>s_heur+1){
                    monotone = false;
                }
                enqueue(nnode,(dist[nnode]+heuristic(nnode,htype)));
            }
            sarr[brow][bcol+1]=sarr[brow][bcol];
            sarr[brow][bcol]=c;
        }
        if(max_depth<dist[u]+1){
            max_depth=dist[u]+1;
        }
    }
    //cout << front << " " << rear;
    cout << "Goal not reachable...";
    cout << "\nNo of explored node: " << node_idx-1 << endl;
    cout << "Depth reachrd out: " << max_depth << endl;
}



int main(){
    string input="";
    string str;
    cout <<"Enter input string :";
    cin >> str;
    input+=str;
    cout << "Enter goal string :";
    cin >> goal;
    int num;
    cout << "If you want to consider empty tile for cost? Enter 1..";
    cin >> num;
    if(num==1){
        costofempty = true;
    }
    cout <<"Enter 1(h1(n)=0) or \n2(h2(n)=no.of misplaced tiles) or \n3(h3(n)=manhattan distance) or \n4(h4(n)=nilsson's sequence score) :";
    int htype;
    cin >> htype;
    if(htype==1){
        cout << "Heuristic used h(n)=0"<<endl;
    }
    if(htype==2){
        cout << "Heuristic used h(n)=no.of misplaced tiles"<<endl;
    }
    if(htype==3){
        cout << "Heuristic used h(n)=Manhattan distance"<<endl;
    }
    if(htype==4){
        cout << "Heuristic used h(n)=Nilsson's sequence score"<<endl;
    }
    auto start = high_resolution_clock::now();
    astar(input,htype);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    float dure=duration.count();
    if(dure>1000000){
        cout << "\nTime taken by function: " << dure/1000000 << "seconds" << endl;
    }
    else{
        cout << "\nTime taken by function: " << dure/1000 << "milliseconds" << endl;
    }
    if(monotone){
        cout << "Monotone is maintained" << endl;
    }
    else{
        cout << "Monotonicity couldn't be maintained" << endl;
    }
 
    return 0;
}
