#include <cstdio>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100100;

struct SuffixArray {
	pair<int, int> sf[MAXN];
	int sa[MAXN], r[MAXN], height[MAXN], h[MAXN];

	struct mycmp {
		pair<int, int> * suffix;
		mycmp(pair<int, int> * suffix_) :
			suffix(suffix_) {
		}
		bool operator()(int lhs, int rhs) {
			return suffix[lhs] < suffix[rhs];
		}
	};

	void init(int n, const char a[MAXN]) {
		sa[0] = 0; // n = 1
		for (int i = 0; i < n; ++i)
			r[i] = a[i];

		for (int i, m = 1; m < n; m <<= 1) {
			for (i = 0; i < n; sa[i] = i++)
				sf[i] = make_pair(r[i], i + m < n ? r[i + m] : -1);
			sort(sa, sa + n, mycmp(sf));
			for (i = 1, r[sa[0]] = 0; i < n; ++i)
				r[sa[i]] = sf[sa[i]] != sf[sa[i - 1]] ? i : r[sa[i - 1]];
		}

		for (int i = 0; i < n; ++i) {
			if (r[i] == 0) {
				h[i] = 0;
			} else {
				int x = i, y = sa[r[i] - 1], z = max(0, h[i - 1] - 1);
				while (x + z < n && y + z < n && a[x + z] == a[y + z]) {
					++z;
				}
				h[i] = z;
			}
		}
		for (int i = 0; i < n; ++i) {
			height[i] = h[sa[i]];
		}
	}
} sa;

int main() {
	char s[1005];
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		int len = strlen(s);
		sa.init(len, s);
		int maxlen = 0, maxi = 0, cnt = 0;
		for (int i = 1; i < len; i++) {
			if (sa.height[i] && sa.height[i] > maxlen) {
				maxlen = sa.height[i], maxi = i, cnt = 2;
			} else if (sa.height[i] && sa.height[i] == maxlen) {
				if (sa.height[i] == sa.height[i - 1])
					cnt++;
			}
		}
		if (cnt == 0)
			printf("%s\n", "No repetitions found!");
		else {
			for (int i = sa.sa[maxi], c = 0; c < maxlen; i++, c++)
				putchar(s[i]);
			printf(" %d\n", cnt);
		}

	}
}
