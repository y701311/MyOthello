#include <Siv3D.hpp>
#include "othello.h"


void Main() {
	othello othe;
	constexpr Point offset(160, 60);

	othe.start();
	
	Scene::SetBackground(Palette::Sandybrown);

	while (System::Update()) {

		Transformer2D tr(Mat3x2::Translate(offset), true);
		
		othe.draw();

		if (othe.turn % 2) {
			othe.color = 1;			//	1 represent black
			othe.nomalSelect();
		}
		else {
			othe.color = -1;		//	-1 represent white
			if (othe.kadoSelect() == 0) {
				if (othe.turn < 25) {
					othe.rondomSelect();
				}
				else {
					othe.maxSelect();
				}
			}
		}

		if (othe.end) {
			if (SimpleGUI::ButtonAt(U"ReStart", Vec2(580, 520))) {
				othe.start();
			}
		}

	}

}