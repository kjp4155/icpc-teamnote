namespace Suffix {
    static const int MX = 100010;
    int RA[MX<<1], t[MX], C[MX];
    
    void build_SA(int N, char A[], int SA[], int LCP[]){
        int cnt = 130;
        for(int i=1;i<=N;i++)RA[i] = A[i];
        for(int i=1;i<=N;i++)C[RA[i]]++;
        for(int i=2;i<=cnt;i++)C[i] += C[i-1];
        for(int i=1;i<=N;i++)SA[C[RA[i]]--] = i;
        for(int i=1;i<=cnt;i++)C[i] = 0;
        for(int L=1;;L<<=1){
            int z = 0;
            for(int i=N-L+1;i<=N;i++)t[++z] = i;
            for(int i=1;i<=N;i++)if(SA[i] > L)t[++z] = SA[i] - L;
            for(int i=1;i<=N;i++)C[RA[i]]++;
            for(int i=2;i<=cnt;i++)C[i] += C[i-1];
            for(int i=N;i;i--)SA[ C[RA[t[i]]]-- ] = t[i];
            for(int i=1;i<=cnt;i++)C[i] = 0;
            cnt = 1;
            for(int i=1;i<=N;i++){
                if(i != 1 && RA[SA[i]] == RA[SA[i-1]] && RA[SA[i] + L] == RA[SA[i-1] + L])C[SA[i]] = cnt-1;
                else C[SA[i]] = cnt++;
            }
            for(int i=1;i<=N;i++)RA[i] = C[i], C[i] = 0;
            if(cnt == N+1)break;
        }
        for(int i=1, L=0;i<=N;i++, L=(L?L-1:0)){
            if(RA[i] == N)continue;
            int t = SA[RA[i]+1];
            while(A[i+L] == A[t+L])++L;
            LCP[RA[i]] = L;
        }
    }
};