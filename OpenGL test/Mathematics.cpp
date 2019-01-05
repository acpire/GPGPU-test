#include "Mathematics.h"

float Mathematics::pushFloat(char* data, float number, size_t length) {
	float _int;
	float _fract;
	_fract = modff(number, &_int);
	int integer = int(_int);
	char _number[12];
	size_t index = 0;
	if (integer < 0 || _fract < 0.0f)
		if (*data != 0 && length != 0) {
			*data = '-';
			data++;
			length--;
			integer = ~integer + 1;
		}
	do {
		_number[index++] = integer % 10 + 48;
		integer /= 10;
	} while (integer != 0);
	for (size_t i = 1; i <= index; i++) {
		if (*data != 0 && length != 0) {
			*data = _number[index - i];
			data++;
			length--;
		}
	}
	if (*data != 0 && length != 0) {
		*data = '.';
		data++;
		length--;
	}
	if (_fract < 0.0f) {
		*((int*)&_fract) ^= 2147483648;
	}
	_fract *= 10;
	do {
		if (*data != 0 && length != 0) {
			*data = int(_fract) + 48;
			_fract -= int(_fract);
			_fract *= 10;
			data++;
			length--;
		}
		else
			break;
	} while (_fract > 0.0001f);
	return 0;
}