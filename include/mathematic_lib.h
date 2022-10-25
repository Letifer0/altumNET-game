#pragma once

namespace math {
	int math::pow(int, int);

	int math::pow(int number, int degree) {
		int tmp = number;
		for (int i = 1; i <= degree; i++) {
			number = number * tmp;
		}
		return number;
	}
}

