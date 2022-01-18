#include "utility.h"

// Алгоритм не мой src: http://stackoverflow.com/a/1449859/412627

sds printfcomma(int n){
	sds num = sdsempty();

	int n2 = 0;
	int scale = 1;
	if (n<0){
		num = sdscat(num, "-");
		n = -n;
	}
	while (n >= 1000){
		n2 = n2 + scale* (n%1000);
		n/=1000;
		scale *= 1000;
	}
	num = sdscatprintf(num, "%d", n);

	while (scale != 1){
		scale /= 1000;
		n = n2 / scale;
		n2 = n2 % scale;
		num = sdscatprintf(num, "%03d", n);
	}
	return num;
}