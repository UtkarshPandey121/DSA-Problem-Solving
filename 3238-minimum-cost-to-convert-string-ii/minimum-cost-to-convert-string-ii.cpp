class Solution {
public:
    long long minimumCost(string source, string target,
                          vector<string>& original,
                          vector<string>& changed,
                          vector<int>& cost) {

        const long long INF = 1e18;
        int n = source.size();
        int m = original.size();

        // Map strings to ids
        unordered_map<string,int> id;
        vector<string> all;

        auto getId = [&](const string& s) {
            if (!id.count(s)) {
                id[s] = all.size();
                all.push_back(s);
            }
            return id[s];
        };

        for (int i = 0; i < m; i++) {
            getId(original[i]);
            getId(changed[i]);
        }

        int K = all.size();
        vector<vector<long long>> dist(K, vector<long long>(K, INF));

        for (int i = 0; i < K; i++) dist[i][i] = 0;

        // Direct transformations
        for (int i = 0; i < m; i++) {
            int u = getId(original[i]);
            int v = getId(changed[i]);
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        // Floyd–Warshall
        for (int k = 0; k < K; k++)
            for (int i = 0; i < K; i++)
                for (int j = 0; j < K; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        // Precompute valid substring lengths
        unordered_set<int> validLens;
        for (auto &s : original) validLens.insert(s.length());

        vector<long long> dp(n + 1, INF);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--) {

            // single character
            if (source[i] == target[i]) {
                dp[i] = dp[i + 1];
            } else {
                string a(1, source[i]), b(1, target[i]);
                if (id.count(a) && id.count(b))
                    dp[i] = min(dp[i], dist[id[a]][id[b]] + dp[i + 1]);
            }

            // only valid substring lengths
            for (int len : validLens) {
                if (i + len > n) continue;

                string s1 = source.substr(i, len);
                string s2 = target.substr(i, len);

                if (id.count(s1) && id.count(s2)) {
                    long long c = dist[id[s1]][id[s2]];
                    if (c < INF)
                        dp[i] = min(dp[i], c + dp[i + len]);
                }
            }
        }

        return dp[0] >= INF ? -1 : dp[0];
    }
};
