
// OR convolution
vector<ll> FFT_OR(vector<ll> A, int rev) {
    int N = A.size(); // A.size() must be power of 2
    for(int len=1;len<N;len<<=1) {
        for(int i=0;i<N;i+=len*2) {
            for(int j=0;j<len;j++) {
                ll x = A[i+j];
                ll y = A[i+j+len];
                if(rev == 0) A[i+j+len] = x + y;
                else A[i+j+len] = y - x;
            }
        }
    }
    return A;
}

// AND convolution
vector<ll> FFT_AND(vector<ll> A, int rev) {
    int N = A.size(); // A.size() must be power of 2
    for(int len=1;len<N;len<<=1) {
        for(int i=0;i<N;i+=len*2) {
            for(int j=0;j<len;j++) {
                ll x = A[i+j];
                ll y = A[i+j+len];
                if(rev == 0) A[i+j] = x + y;
                else A[i+j] = x - y;
            }
        }
    }
    return A;
}

// XOR convolution
vector<ll> FFT_XOR(vector<ll> A, int rev) {
    int N = A.size(); // A.size() must be power of 2
    for(int len=1;len<N;len<<=1) {
        for(int i=0;i<N;i+=len*2) {
            for(int j=0;j<len;j++) {
                ll x = A[i+j];
                ll y = A[i+j+len];
                A[i+j] = x + y;
                A[i+j+len] = x - y;
            }
        }
    }
    if(rev) rep(i, N) A[i] /= N;
    return A;
}

const int L = 10;
const int N = 1<<L;
int main() {
    vector<ll> A(N),B(N);
    rep(i, N) A[i] = rand() % 1000;
    rep(i, N) B[i] = rand() % 1000;
    ll EX[N] = {};
    rep(i, N) rep(j, N) EX[i&j] = EX[i&j] + A[i] * B[j];
    A = FFT_AND(A, 0);
    B = FFT_AND(B, 0);
    rep (i, N) A[i] = A[i] * B[i];
    A = FFT_AND(A, 1);
    rep(i, N) printf("%lld %lld\n", A[i], EX[i]);
    return 0;
}