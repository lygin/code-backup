#include <bits/stdc++.h>
using namespace std;

int main() {
	int col;
	char c;
	scanf("%d %c", &col, &c);
	int row = (int)(col/2.0+0.5);
	for(int i=0; i<row; ++i) {
		if(i == 0 || i == row-1) {
			for(int j=0; j<col; ++j)
				printf("%c", c);
		}
		else {
			for(int j=0; j<col; ++j) {
				if(j == 0 || j == col-1)
				printf("%c", c);
				else printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
} 
