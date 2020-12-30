#include <Siv3D.hpp>
#include "othello.h"


void const othello::drawGridLines() {

	for (auto i : { 0, 1, 2, 3, 4, 5, 6, 7, 8 }) {
		Line(i * 60, 0, i * 60, 480).draw(2, ColorF(0.2));
		Line(0, i * 60, 480, i * 60).draw(2, ColorF(0.2));
	}

}

void const othello::drawCells() {

	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {

			const Rect cell((j - 1) * CellSize, (i - 1) * CellSize, CellSize, CellSize);

			if (masu[i][j] == black) {
				Circle(cell.center(), CellSize * 0.4).draw(Palette::Black);
				continue;
			}
			else if (masu[i][j] == white) {
				Circle(cell.center(), CellSize * 0.4).draw(Palette::White);
				continue;
			}

			if (cell.mouseOver()) {

				Cursor::RequestStyle(CursorStyle::Hand);
				cell.stretched(-2).draw(ColorF(1.0, 0.6));

			}

		}
	}

}

void othello::makeButtons() {

	if (SimpleGUI::ButtonAt(U"Pass", Vec2(580, 0))) {
		turn++;
	}

}

void othello::draw() {

	ClearPrint();

	if (!end) {
		if (turn % 2) {
			Print << U"���̃^�[���ł��B";
		}
		else {
			Print << U"���̃^�[���ł��B";
		}
	}

	if (end) {
		last();
	}

	drawGridLines();
	drawCells();
	if (!end) {
		makeButtons();
	}

}

void othello::start() {

	turn = 1;
	end = false;

	for (int32 i = 0; i < 10; i++) {
		for (int32 j = 0; j < 10; j++) {
			masu[i][j] = 0;
			masuBefore[i][j] = 0;
		}
	}

	masu[4][4] = white;
	masu[5][5] = white;
	masu[4][5] = black;
	masu[5][4] = black;

	masuBefore[4][4] = white;
	masuBefore[5][5] = white;
	masuBefore[4][5] = black;
	masuBefore[5][4] = black;

}

void othello::turnOver(int32 x, int32 y) {
	int32 i;

	for (i = x - 1; masu[i][y] * -1 == masu[x][y]; i--) {//	�c
		if (masu[i - 1][y] == masu[x][y]) {
			for (i = x - 1; masu[i][y] * -1 == masu[x][y]; i--) {
				masu[i][y] *= -1;
			}
			break;
		}
	}
	for (i = x + 1; masu[i][y] * -1 == masu[x][y]; i++) {
		if (masu[i + 1][y] == masu[x][y]) {
			for (i = x + 1; masu[i][y] * -1 == masu[x][y]; i++) {
				masu[i][y] *= -1;
			}
			break;
		}
	}
	for (i = y - 1; masu[x][i] * -1 == masu[x][y]; i--) {//	��
		if (masu[x][i - 1] == masu[x][y]) {
			for (i = y - 1; masu[x][i] * -1 == masu[x][y]; i--) {
				masu[x][i] *= -1;
			}
			break;
		}
	}
	for (i = y + 1; masu[x][i] * -1 == masu[x][y]; i++) {
		if (masu[x][i + 1] == masu[x][y]) {
			for (i = y + 1; masu[x][i] * -1 == masu[x][y]; i++) {
				masu[x][i] *= -1;
			}
			break;
		}
	}
	for (i = 1; masu[x - i][y - i] * -1 == masu[x][y]; i++) {//	���΂�
		if (masu[x - i - 1][y - i - 1] == masu[x][y]) {
			for (i = 1; masu[x - i][y - i] * -1 == masu[x][y]; i++) {
				masu[x - i][y - i] *= -1;
			}
			break;
		}
	}
	for (i = 1; masu[x + i][y + i] * -1 == masu[x][y]; i++) {
		if (masu[x + i + 1][y + i + 1] == masu[x][y]) {
			for (i = 1; masu[x + i][y + i] * -1 == masu[x][y]; i++) {
				masu[x + i][y + i] *= -1;
			}
			break;
		}
	}
	for (i = 1; masu[x + i][y - i] * -1 == masu[x][y]; i++) {//	�E�΂�
		if (masu[x + i + 1][y - i - 1] == masu[x][y]) {
			for (i = 1; masu[x + i][y - i] * -1 == masu[x][y]; i++) {
				masu[x + i][y - i] *= -1;
			}
			break;
		}
	}
	for (i = 1; masu[x - i][y + i] * -1 == masu[x][y]; i++) {
		if (masu[x - i - 1][y + i + 1] == masu[x][y]) {
			for (i = 1; masu[x - i][y + i] * -1 == masu[x][y]; i++) {
				masu[x - i][y + i] *= -1;
			}
			break;
		}
	}

}

int32 othello::judge(int32 x, int32 y) {
	int32 i, can = 0;

	for (i = x - 1; masu[i][y] * -1 == masu[x][y]; i--) {//	�c
		if (masu[i - 1][y] == masu[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = x + 1; masu[i][y] * -1 == masu[x][y]; i++) {
		if (masu[i + 1][y] == masu[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = y - 1; masu[x][i] * -1 == masu[x][y]; i--) {//	��
		if (masu[x][i - 1] == masu[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = y + 1; masu[x][i] * -1 == masu[x][y]; i++) {
		if (masu[x][i + 1] == masu[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = 1; masu[x - i][y - i] * -1 == masu[x][y]; i++) {//	���΂�
		if (masu[x - i - 1][y - i - 1] == masu[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = 1; masu[x + i][y + i] * -1 == masu[x][y]; i++) {
		if (masu[x + i + 1][y + i + 1] == masu[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = 1; masu[x + i][y - i] * -1 == masu[x][y]; i++) {//	�E�΂�
		if (masu[x + i + 1][y - i - 1] == masu[x][y]) {
			can = 1;
			break;
		}
	}
	for (i = 1; masu[x - i][y + i] * -1 == masu[x][y]; i++) {
		if (masu[x - i - 1][y + i + 1] == masu[x][y]) {
			can = 1;
			break;
		}
	}

	return can;
}

int32 othello::canPutColor(int32 x, int32 y) {

	if (masu[x][y] == 0) {
		masu[x][y] = color;
		if (judge(x, y)) {
			masu[x][y] = 0;
			return 1;
		}
		masu[x][y] = 0;
	}

	return 0;
}

void othello::nomalSelect() {

	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {

			const Rect cell((j - 1) * CellSize, (i - 1) * CellSize, CellSize, CellSize);

			if ((masu[i][j] == 0) && cell.leftClicked()) {

				if (canPutColor(i, j)) {
					masu[i][j] = color;
					turnOver(i, j);
					if (postProcess()) {
						end = true;
					}
				}

			}

		}
	}

}

int32 othello::kadoSelect() {
	bool kado = false;

	if (canPutColor(1, 1)) {
		masu[1][1] = color;
		turnOver(1, 1);
		kado = true;
	}
	if (canPutColor(1, 8)) {
		masu[1][8] = color;
		turnOver(1, 8);
		kado = true;

	}
	if (canPutColor(8, 1)) {
		masu[8][1] = color;
		turnOver(8, 1);
		kado = true;
	}
	if (canPutColor(8, 8)) {
		masu[8][8] = color;
		turnOver(8, 8);
		kado = true;
	}


	if (kado) {
		if (postProcess()) {
			end = true;
		}
		return 1;
	}

	return 0;
}

int32 othello::rondomSelect() {
	int32 i, j;
	int32 x, y;
	int32 can = 0;
	int32 kadoCancel = 0;

	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {

			if (canPutColor(i, j)) {
				can++;
			}

		}
	}
	if (can == 0) {
		turn++;
		return 0;
	}

	srand((unsigned)time(NULL));
	while (1) {
		x = rand() % 8 + 1;
		y = rand() % 8 + 1;

		if (canPutColor(x, y)) {

			masu[x][y] = color;
			turnOver(x, y);

			if (kadoCancel > 15) {
				break;
			}
			color *= -1;
			if (canPutColor(1, 1) || canPutColor(8, 1) || canPutColor(1, 8) || canPutColor(8, 8)) {
				color *= -1;
				kadoCancel++;
				for (i = 1; i < 9; i++) {
					for (j = 1; j < 9; j++) {
						masu[i][j] = masuBefore[i][j];
					}
				}
			}
			else {
				break;
			}

		}

	}

	if (postProcess()) {
		end = true;
	}

	return 0;
}

int32 othello::count(int32 x, int32 y) {
	int32 i, countKoma = 0;

	for (i = x - 1; masu[i][y] * -1 == masu[x][y]; i--) {//	�c
		if (masu[i - 1][y] == masu[x][y]) {
			for (i = x - 1; masu[i][y] * -1 == masu[x][y]; i--) {
				countKoma++;
			}
			break;
		}
	}
	for (i = x + 1; masu[i][y] * -1 == masu[x][y]; i++) {
		if (masu[i + 1][y] == masu[x][y]) {
			for (i = x + 1; masu[i][y] * -1 == masu[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = y - 1; masu[x][i] * -1 == masu[x][y]; i--) {//	��
		if (masu[x][i - 1] == masu[x][y]) {
			for (i = y - 1; masu[x][i] * -1 == masu[x][y]; i--) {
				countKoma++;
			}
			break;
		}
	}
	for (i = y + 1; masu[x][i] * -1 == masu[x][y]; i++) {
		if (masu[x][i + 1] == masu[x][y]) {
			for (i = y + 1; masu[x][i] * -1 == masu[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = 1; masu[x - i][y - i] * -1 == masu[x][y]; i++) {//	���΂�
		if (masu[x - i - 1][y - i - 1] == masu[x][y]) {
			for (i = 1; masu[x - i][y - i] * -1 == masu[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = 1; masu[x + i][y + i] * -1 == masu[x][y]; i++) {
		if (masu[x + i + 1][y + i + 1] == masu[x][y]) {
			for (i = 1; masu[x + i][y + i] * -1 == masu[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = 1; masu[x + i][y - i] * -1 == masu[x][y]; i++) {//	�E�΂�
		if (masu[x + i + 1][y - i - 1] == masu[x][y]) {
			for (i = 1; masu[x + i][y - i] * -1 == masu[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}
	for (i = 1; masu[x - i][y + i] * -1 == masu[x][y]; i++) {
		if (masu[x - i - 1][y + i + 1] == masu[x][y]) {
			for (i = 1; masu[x - i][y + i] * -1 == masu[x][y]; i++) {
				countKoma++;
			}
			break;
		}
	}

	return countKoma;
}

int32 othello::maxSelect() {
	int32 i, j;
	int32 x[60] = { 0 }, y[60] = { 0 };
	int32 can = 0;
	int32 countColor, max = 1, maxPlace = 0;
	int32 kadoCancel = 0;

	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {

			if (canPutColor(i, j)) {
				can++;
			}

		}
	}
	if (can == 0) {
		turn++;
		return 0;
	}

	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {

			if (masu[i][j] == 0) {

				masu[i][j] = color;
				countColor = count(i, j);
				masu[i][j] = 0;

				if (max < countColor) {
					max = countColor;
					for (int32 c = 0; c <= maxPlace; c++) {
						x[c] = 0;
						y[c] = 0;
					}
					maxPlace = 0;
				}
				if (max == countColor) {
					x[maxPlace] = i;
					y[maxPlace] = j;
					maxPlace++;
				}

			}

		}
	}

	srand((unsigned)time(NULL));
	while (1) {
		int32 k = rand() % maxPlace;
		masu[x[k]][y[k]] = color;
		turnOver(x[k], y[k]);

		if (kadoCancel > 15) {
			break;
		}
		color *= -1;
		if (canPutColor(1, 1) || canPutColor(8, 1) || canPutColor(1, 8) || canPutColor(8, 8)) {
			color *= -1;
			kadoCancel++;
			for (i = 1; i < 9; i++) {
				for (j = 1; j < 9; j++) {
					masu[i][j] = masuBefore[i][j];
				}
			}
		}
		else {
			break;
		}
	}
	
	if (postProcess()) {
		end = true;
	}

	return 0;
}

int othello::postProcess() {
	int32 can_put = 0;

	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {
			masuBefore[i][j] = masu[i][j];
		}
	}

	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {

				color = black;
				if (canPutColor(i, j)) {
					can_put++;
				}
				color = white;
				if (canPutColor(i, j)) {
					can_put++;
				}
				
		}
	}

	turn++;

	if (can_put > 0) {
		return 0;
	}
	else {
		return 1;
	}

}

void othello::last() {

	int32 black_count = 0, white_count = 0;
	for (int32 i = 1; i < 9; i++) {
		for (int32 j = 1; j < 9; j++) {
			if (masu[i][j] == black) {
				black_count++;
			}
			if (masu[i][j] == white) {
				white_count++;
			}
		}
	}

	if (black_count > white_count) {
		Print << U"���̏����I";
	}
	else if (white_count > black_count) {
		Print << U"���̏����I";
	}
	else {
		Print << U"���������I";
	}
	Print << U"";
	Print << U"�� �c " << black_count << U"�@" << U"�� �c " << white_count;

}