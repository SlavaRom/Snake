#pragma once

int random(int a, int b) {
	return a + rand() % (b - a + 1);
}