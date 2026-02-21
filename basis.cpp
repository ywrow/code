#define int long long

struct bas{
    int p[63],cnt;
    bool z;
    
    bas(){
        memset(p,0,sizeof(p));
        cnt=0;z=0;
    }
    
    // 原插入逻辑封装，供运算符调用
    bool ins(int x){
        for(int i=62;i>=0;i--){
            if(x&(1LL<<i)){
                if(!p[i]){
                    p[i]=x;cnt++;
                    return 1;
                }
                x^=p[i];
            }
        }
        z=1;return 0;
    }
    
    // += 插入元素
    bas& operator +=(int x){
        ins(x);
        return *this;
    }
    
    // += 合并线性基
    bas& operator +=(const bas& oth){
        for(int i=0;i<=62;i++) if(oth.p[i]) ins(oth.p[i]);
        if(oth.z) z=1;
        return *this;
    }
    
    // + 插入 (返回副本)
    bas operator +(int x) const {
        bas res=*this;
        res+=x;
        return res;
    }
    
    // + 合并 (返回副本)
    bas operator +(const bas& oth) const {
        bas res=*this;
        res+=oth;
        return res;
    }
    
    int qmax(){
        int res=0;
        for(int i=62;i>=0;i--) res=max(res,res^p[i]);
        return res;
    }
    
    int qmin(){
        if(z) return 0;
        for(int i=0;i<=62;i++) if(p[i]) return p[i];
        return 0;
    }
    
    bool cx(int x){
        for(int i=62;i>=0;i--){
            if(x&(1LL<<i)){
                if(p[i]) x^=p[i];
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
        int cp[63]; memcpy(cp,p,sizeof(p));
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
        memset(p,0,sizeof(p));
        cnt=0;z=0;
    }
};
