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

		/// \brief
		/// Setting the change variable signals to the levelManager that the level pointer needs to be updated
		void change(int type) {
			if (updateable) {
				OrderType = type;
				set = true;
				updateable = false;
			}
		}
		/// \brief
		/// Unused to check if the change method is called
		bool getSet() {
			return set;
		}
		/// \brief
		/// acquiring the containers value
		int getOrderType() {
			set = false;
			updateable = true;
			return OrderType;
		}
	};
