#include<iostream>
#include<vector>
#include<utility>
#define MAXN 1000005
using namespace std;
struct Node {
  int val, size, par, l, r;
};
class ScapeGoat {
  Node BST[MAXN]={}; //dummy node at 1000004
  vector <pair<int,int> > vals;
public:
  int sz=0, Root=0;
  void init() {
    add(-1,MAXN-1);
    vals.reserve(MAXN);
  }
  void add(int val, int par) {
    BST[sz].val=val;
    BST[sz].size=1;
    BST[sz].par=par;
    BST[sz].l=MAXN-1;
    BST[sz].r=MAXN-1;
    sz++;
  }
  void Inorder(int at) {
    if (at == MAXN-1) {return;}
    Inorder(BST[at].l);
    vals.push_back({BST[at].val,at});
    Inorder(BST[at].r);
  }
  void Out() {
    vals.clear();
    Inorder(Root);
     for (int i=1; i<vals.size(); i++) {
      printf("%d\n", vals[i].first);
    }
  }
  int Build(int l, int r, int par) {
    if (l > r) {return(MAXN-1);}
    int mid=(l+r)>>1;
    if (l == r) {
      BST[vals[l].second].l=BST[vals[l].second].r=MAXN-1;
    } else {
        BST[vals[mid].second].l=Build(l, mid-1,vals[mid].second);
        BST[vals[mid].second].r=Build(mid+1,r,vals[mid].second);
    }
    BST[vals[mid].second].size=r-l+1;
    BST[vals[mid].second].par=par;
    if (par == MAXN-1) {Root=vals[mid].second;}
    return(vals[mid].second);
  }
  int rebuild(int at) {
    vals.clear();
    Inorder(at);
    int res=Build(0, vals.size()-1, BST[at].par);
    return(res);
  }
  void Insert(int at, int ind, int val, bool bal) {
    bool off=max(BST[BST[at].l].size,BST[BST[at].r].size)*3 > BST[at].size*2; //imbalanced
      if (BST[BST[at].l].size+1 <= ind) {
        if (BST[BST[at].r].size == 0) {
          //no right child
          add(val, at);
          BST[at].r=sz-1;
        } else {
          Insert(BST[at].r, ind-BST[BST[at].l].size-1, val, off);
        }
      } else {
        if (BST[BST[at].l].size == 0) {
          //no left child
          add(val, at);
          BST[at].l=sz-1;
        } else {
            Insert(BST[at].l, ind, val, off);
        }
      }
      BST[at].size=BST[BST[at].l].size+BST[BST[at].r].size+1;
      if (bal && off) {
        //alpha = 2/3
        int par=BST[at].par, newrt=rebuild(at);
        if (par == MAXN-1) {return;}
        if (BST[par].l == at) {
          BST[par].l=newrt;
        } else {
          BST[par].r=newrt;
        }
      }
  }
} arr;