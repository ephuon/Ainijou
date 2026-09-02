int minimal_string(){// 下标从0开始
	int k = 0, i = 0, j = 1;
	while(k < n && i < n && j < n){
		if(a[(i+k)%n] == a[(j+k)%n]) {k++; continue;}
		if(a[(i+k)%n] > a[(j+k)%n]) i = i+k+1;
		else j = j+k+1;
		i += (i == j); k = 0; }
	return min(i, j); } 
