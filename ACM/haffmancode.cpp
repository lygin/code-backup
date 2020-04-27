#include <bits/stdc++.h>
using namespace std;

int *w;  // store weight
int n;  // number of char

typedef struct TreeNode
{
	int weight;
	int parent, lchild, rchild;
}*HaffmanTree;

typedef char* *HuffmanCode;

void Select(HaffmanTree HT, int n, int s1, int s2) {
	int mi1 = INT_MAX;
	int mi2 = INT_MAX;
	s1 = 0;
	s2 = 0;
	for(int i=1; i<=n; ++i)
		if(HT[i].weight < mi1) {
			mi1 = HT[i].weight;
			s1 = i;
		}
	for(int i=1; i<=n; ++i) {
		if(i == s1) continue;
		if(HT[i].weight < mi2) {
			mi2 = HT[i].weight;
			s2 = i;
		}
	}
}
void HuffmanCoding (HaffmanTree &HT, HuffmanCode &HC) {
	if(n <= 1) return;
	int m = 2 * n - 1;  // number of tree node
	HT = (HaffmanTree)malloc((m + 1) * sizeof(TreeNode));  // 0 not use
	int i;
	HaffmanTree p;
	for(p = HT + 1, i = 1; i<=n; ++i, ++p, ++w)
		*p = {*w, 0, 0, 0};
	for(; i<=m; ++i, ++p)
		*p = {0, 0, 0, 0};
	for(i=n+1; i<=m; ++i) {  // set up Huffmantree
		int s1, s2;
		Select(HT, i-1, s1, s2);  // find smallest two that parent is 0
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[s1].parent = i;
		HT[s2].parent = i;
	}
	HC = (HuffmanCode)malloc((n+1) * sizeof(char *));  // assign n string ptr; 0 not use
	char *cd = (char *)malloc(n*sizeof(char));
	cd[n-1] = '\0';
	for(int i=1; i<=n; ++i) {
		int start = n-1;
		int c,f;
		for(c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent) {
			if(HT[f].lchild = c) cd[--start] = '0';
			else cd[--start] = '1';
			HC[i] = (char *)malloc((n-start)*sizeof(char));
			strcpy(HC[i], &cd[start]);
		}
	}
	free(cd);
}

int main() {
	// initialization
	scanf("%d", &n);
	w = (int *)malloc(n * sizeof(int));
	for(int i=0; i<n; ++i)
		scanf("%d", w+i);
	HaffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC);
	return 0;
}

