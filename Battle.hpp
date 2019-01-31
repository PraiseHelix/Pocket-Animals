#pragma once

class Battle {
private:
	bool set = false;
	unsigned int id = 0;

public:
		void start(unsigned int id) {
			set = true;
			setId(id);
		}
		void setId(unsigned int newId) {
			id = newId;
		}

		// leader ID
		unsigned int getId() {
			return id;
		};
		bool backSwitchBattle(bool wipe = false) {
			bool setb = set;
			if (wipe) {
				set = !set;
			}
			return setb;
			
		};
};