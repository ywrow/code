#include<bits/stdc++.h>
using namespace std;
#define int long long

struct linear_basis{
    int p[63],cnt;
    bool z;
    
    linear_basis(){
        memset(p,0,sizeof(p));
        cnt=0;
        z=0;
    }
    
    //插入
    bool ins(int x){
        for(int i=62;i>=0;i--){
            if(x&(1LL<<i)){
                if(!p[i]){
                    p[i]=x;
                    cnt++;
                    return 1;
                }
                x^=p[i];
            }
        }
        z=1;
        return 0;
    }
    
    //查询最大值
    int qmax(){
        int res=0;
        for(int i=62;i>=0;i--){
            res=max(res,res^p[i]);
        }
        return res;
    }
    
    //查询最小值
    int qmin(){
        if(z)return 0;
        for(int i=0;i<=62;i++){
            if(p[i])return p[i];
        }
        return 0;
    }
    
    //判断是否可异或出
    bool cx(int x){
        for(int i=62;i>=0;i--){
            if(x&(1LL<<i)){
                if(p[i])x^=p[i];
                else return 0;
            }
        }
        return 1;
    }
    
    //计算可异或出的数的个数
    int cntxor(){
        if(cnt==0)return z?1:0;
        int tot=(1LL<<cnt);
        return z?tot:tot-1;
    }
    
    //查询第k小值
	 
	int qk(int k){
		k-=z;
		if(!k)return 0;
		int tmp[65];
		int cnt=0,res=0;
		for(int i=0;i<=61;i++){
			for(int j=i-1;j>=0;j--){
				if(p[i]&(1LL<<j))p[i]^=p[j];
			}
			if(p[i])tmp[cnt++]=p[i];
		}
	    if(k>=(1LL<<cnt))return -1;
	    for(int i=0;i<cnt;i++){
	        if((k>>i)&1)res^=tmp[i];
		}
	    return res;
	}
    
    //线性基合并
    int merge(const linear_basis& oth){
        int add=0;
        for(int i=0;i<=62;i++){
            if(oth.p[i]&&ins(oth.p[i])){
                add++;
            }
        }
        if(oth.z)z=1;
        return add;
    }
    
    //获取有效元素个数
    int size(){return cnt;}
    
    //清空线性基
    void clear(){
        memset(p,0,sizeof(p));
        cnt=0;
        z=0;
    }
};

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin>>n;
    linear_basis lb;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        lb.ins(a);
    }
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int x;cin>>x;
            lb.ins(x);
        }else if(op==2){
            cout<<lb.qmax()<<"\n";
        }else if(op==3){
            cout<<lb.qmin()<<"\n";
        }else if(op==4){
            int k;cin>>k;
            cout<<lb.qk(k)<<"\n";
        }else if(op==5){
            int x;cin>>x;
            cout<<lb.cx(x)<<"\n";
        }else if(op==6){
            cout<<lb.cntxor()<<"\n";
        }else if(op==7){
            int m;cin>>m;
            linear_basis lb2;
            for(int i=1;i<=m;i++){
                int a;cin>>a;
                lb2.ins(a);
            }
            lb.merge(lb2);
        }
    }
}
