for(int i=1; i<=n; i++) {
	while(top > 0 && p[z[top]] > p[i])
		son[i][0] = z[top], top--;
	if(top) son[z[top]][1] = i;
	z[++top] = i;
}