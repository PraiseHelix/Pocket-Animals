#pragma once
#include "..\SGPE\GameObject.hpp"
#include "InputHandler.hpp"
#include <iostream>
class LevelManagerPocketAnimalsSync {
	
	private:
		int OrderType = 0;
		bool set = false;
		bool updateable = true;
	public:
		void change(int type) {
			if (updateable) {
				OrderType = type;
				set = true;
				updateable = false;
			}
		}
		bool getSet() {
			return set;
		}
		int getOrderType() {
	
			set = false;
			updateable = true;
			return OrderType;
		}
	};
