#define int long long

struct bas{
    int b[63],cnt;
    bool z;
    
    bas(){
        memset(b,0,sizeof(b));
        cnt=0;z=0;
    }
    
    int operator [](int x){
    	return b[x];
	}
	
    bool insert(int x){
        for(int i=62;i>=0;i--){
            if(x&(1LL<<i)){
                if(!b[i]){
                    b[i]=x;cnt++;
                    return 1;
                }
                x^=b[i];
            }
        }
        z=1;return 0;
    }
    
    bas& operator +=(int x){
        insert(x);
        return *this;
    }
    
    bas& operator +=(const bas& x){
        for(int i=0;i<=62;i++) if(x.b[i]) insert(x.b[i]);
        if(x.z) z=1;
        return *this;
    }
    
    bas operator +(int x) const {
        bas res=*this;
        res+=x;
        return res;
    }
    
    bas operator +(const bas& x) const {
        bas res=*this;
        res+=x;
        return res;
    }
    
    int qmax(){
        int res=0;
        for(int i=62;i>=0;i--) res=max(res,res^b[i]);
        return res;
    }
    
    int qmin(){
        if(z) return 0;
        for(int i=0;i<=62;i++) if(b[i]) return b[i];
        return 0;
    }
    
    bool cx(int x){
        for(int i=62;i>=0;i--){
            if(x&(1LL<<i)){
                if(b[i]) x^=b[i];
                else return 0;
            }
        }
        return 1;
    }
    
    int nt(){
        if(cnt==0) return z?1:0;
        int tot=(1LL<<cnt);
        return z?tot:tot-1;
    }
    
    int qk(int k){
        k-=z;
        if(!k) return 0;
        int tmp[65],t_cnt=0,res=0;
        int cp[63];
		memcpy(cp,b,sizeof(b));
        for(int i=0;i<=62;i++){
            for(int j=i-1;j>=0;j--) if(cp[i]&(1LL<<j)) cp[i]^=cp[j];
            if(cp[i]) tmp[t_cnt++]=cp[i];
        }
        if(k>=(1LL<<t_cnt)) return -1;
        for(int i=0;i<t_cnt;i++) if((k>>i)&1) res^=tmp[i];
        return res;
    }
    
    int size(){return cnt;}
    
    void clear(){
        memset(b,0,sizeof(b));
        cnt=0;z=0;
    }
};