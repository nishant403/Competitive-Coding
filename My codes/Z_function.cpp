const ll N = 1e6+5;
vector<ll> z(N);

void compute_z(string &s)
{
	ll n = s.length();
	ll len = 0;
	for (ll i = 1; i < n; ++i) {
		if (len >= 1) {
			len = min(z[1], len - 1);
		}
		while (i + len < n and s[i + len] == s[len]) {
			++len;
		}
		z[i] = len;
	}
	return;
}