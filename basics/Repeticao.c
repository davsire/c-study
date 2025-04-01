#include <stdio.h>
#include <stdbool.h>

int main() {
	
	// WHILE
	if (false) {
		int i = 1;
		
		while (i <= 10) {
			printf("%d ", i);
			i++;
		}
	}
	
	// DO-WHILE
	if (false) {
		int j = 1;

		do {
			printf("%d ", j);
			j++;
		} while (j <= 10);	
	}
	
	// FOR
	if (false) {
		int i;
		
		for (i = 1; i <= 10; i++) {
			printf("%d ", i);
		}
	}
	
	// BREAK & CONTINUE
	if (true) {
		int i;
		
		for (i = 1; i <= 10; i++) {
			if (i == 5) {
				continue;
			}
			printf("%d ", i);
			// if (i == 5) {
			//	break;
			// }
		}
	}
}
