mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct treap{
	struct Node{
		int siz,v,r,ls,rs;
	}t[2000001];
	int tot,root;
	treap(){
		tot=0;
		root=0;
	}
	int newnode(int v){
		++tot;
		t[tot].v=v;
		t[tot].r=rnd();
		t[tot].siz=1;
		t[tot].ls=t[tot].rs=0;
		return tot;
	}
	void push_up(int u){
		if(!u)return;
		t[u].siz=t[t[u].ls].siz+t[t[u].rs].siz+1;
	}
	void splitv(int u,int v,int &L,int &R){
		if(!u){
			L=R=0;
			return;
		}
		if(t[u].v<=v){
			L=u;
			splitv(t[u].rs,v,t[u].rs,R);
		}else{
			R=u;
			splitv(t[u].ls,v,L,t[u].ls);
		}
		push_up(u);
	}
	void splitr(int u,int k,int &L,int &R){
		if(!u){
			L=R=0;
			return;
		}
		int ls_siz=t[t[u].ls].siz;
		if(k<=ls_siz){
			R=u;
			splitr(t[u].ls,k,L,t[R].ls);
		}else{
			L=u;
			splitr(t[u].rs,k-ls_siz-1,t[L].rs,R);
		}
		push_up(u);
	}
	int merge(int L,int R){
		if(!L||!R)return L+R;
		if(t[L].r<t[R].r){
			t[L].rs=merge(t[L].rs,R);
			push_up(L);
			return L;
		}else{
			t[R].ls=merge(L,t[R].ls);
			push_up(R);
			return R;
		}
	}
	void insert(int v){
		int u=root,z=newnode(v),f=0;
		while(u&&t[u].r<t[z].r){
			f=u;
			t[u].siz++;
			if(v<t[u].v)u=t[u].ls;
			else u=t[u].rs;
		}
		if(f){
			if(v<t[f].v)t[f].ls=z;
			else t[f].rs=z;
		}else{
			root=z;
		}
		splitv(u,v,t[z].ls,t[z].rs);
		push_up(z);
	}
	void del(int v){
		int u=root,f=0;
		while(u&&t[u].v!=v){
			f=u;
			t[u].siz--;
			if(v<t[u].v)u=t[u].ls;
			else u=t[u].rs;
		}
		if(u){
			int new_sub=merge(t[u].ls,t[u].rs);
			if(f){
				if(v<t[f].v)t[f].ls=new_sub;
				else t[f].rs=new_sub;
			}else{
				root=new_sub;
			}
		}
	}
	int queryr(int v){
		int L,R;
		splitv(root,v-1,L,R);
		int ans=t[L].siz+1;
		root=merge(L,R);
		return ans;
	}
	int queryv(int k){
		int u=root;
		while(u){
			int ls_siz=t[t[u].ls].siz;
			if(k<=ls_siz)u=t[u].ls;
			else if(k==ls_siz+1)return t[u].v;
			else{
				k-=(ls_siz+1);
				u=t[u].rs;
			}
		}
		return -1;
	}
	int prev(int v){
		int L,R,u;
		splitv(root,v-1,L,R);
		u=L;
		while(u&&t[u].rs)u=t[u].rs;
		int ans;
		if(u)ans=t[u].v;
		else ans=-2147483648;
		root=merge(L,R);
		return ans;
	}
	int nextv(int v){
		int L,R,u;
		splitv(root,v,L,R);
		u=R;
		while(u&&t[u].ls)u=t[u].ls;
		int ans;
		if(u)ans=t[u].v;
		else ans=2147483647;
		root=merge(L,R);
		return ans;
	}
}t;
