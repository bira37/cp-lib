int spt[MAXN][LOGN];
int e[MAXN];

void spt_build(int *a, int n) {
    for(int i = 0; i < n; i++) {
        spt[i][0] = a[i];
    }

    for(int i = 1; (1<<i) <= n; i++) {
        for(int j = 0; j+(1<<i) <= n; j++) {
            spt[j][i] = min(spt[j][i-1], spt[j+(1<<(i-1))][i-1]);
        }
    }

    int k = 0;
    for(int j = 0; (1<<j) <= 2*n; j++) {
        for(; k <= n && k < (1<<j); k++) {
            e[k] = j-1;
        }
    }
}

int spt_rmq(int l, int r) {
    return min(spt[l][e[sz]], spt[r-(1<<e[sz])+1][e[sz]]);
}
