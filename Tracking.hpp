#pragma once
#include <memory>
#include <unordered_map>

class PlayerProgress{
public:

public:
	bool waterLeaderBottle = false;
	bool landLeaderSwitchBlade = false;
	bool flightLeaderCarKeys = false;
	bool fireExtinguisher = false;
	int pocketAnimalsFought = 0;

	void increasePocketAnimalsFought() {
		pocketAnimalsFought += 1;
	}

	/// \brief
	/// Used to set the item id i.e. based on a object id setting the found flag
	void setItemById(int id) {
		switch (id) {
			case 5:
				waterLeaderBottle = true;
				break;
			case 6:
				 landLeaderSwitchBlade = true;
				 break;
			case 7:
				 flightLeaderCarKeys = true;
				 break;
			case 8:
				fireExtinguisher = true;
				break;
		}
	}
};



class NPCLeader {
private:
public:
	NPCLeader() {};
	virtual bool condition() = 0;

	/// \brief
	/// return the text of a player for dialog
	virtual std::vector<std::string> getText() = 0;
	virtual unsigned int getId() = 0;
};

class FireLeader : public NPCLeader {
private:
	std::shared_ptr<PlayerProgress> progress;
	std::vector<std::string> text;
	unsigned int id = 0;
public:
	FireLeader() {};
	FireLeader(std::shared_ptr<PlayerProgress> progress, std::vector<std::string> text, unsigned int id) :progress(progress), text(text), id(id) {};


	void setText(std::vector<std::string> t) {
		text = t;
	}
	void setPlayerProgress(std::shared_ptr<PlayerProgress> p) {
		progress = p;
	}

	unsigned int getId() {
		return id;
	}

	bool condition() {
		if (progress->fireExtinguisher) {
			if (progress->pocketAnimalsFought > 6) {
				return true;
			}
		}
		return false;
	};

	std::vector<std::string> getText() {
		// TODO conditional advice
		// IE : "you might have luck north of the valley after asking a series of times
		return text;
	}
};
class LandLeader : public NPCLeader {
private:
	std::shared_ptr<PlayerProgress> progress;
	std::vector<std::string> text;
	unsigned int id = 0;
public:
	LandLeader() {};
	LandLeader(std::shared_ptr<PlayerProgress> progress, std::vector<std::string> text, unsigned int id) :progress(progress), text(text), id(id) {};

	void setText(std::vector<std::string> t) {
		text = t;
	}
	void setPlayerProgress(std::shared_ptr<PlayerProgress> p) {
		progress = p;
	}

	unsigned int getId() {
		return id;
	}

	bool condition() {
		if (progress->landLeaderSwitchBlade) {
			if (progress->pocketAnimalsFought > 8) {
				return true;
			}
		}
		return false;
	};

	std::vector<std::string> getText() {
		// TODO conditional advice
		// IE : "you might have luck north of the valley after asking a series of times
		return text;
	}
};


class EndBoss : public NPCLeader {
private:
	std::shared_ptr<PlayerProgress> progress;
	std::vector<std::string> text;
	unsigned int id = 0;
public:
	EndBoss() {};
	EndBoss(std::shared_ptr<PlayerProgress> progress, std::vector<std::string> text, unsigned int id) :progress(progress), text(text), id(id) {};

	void setText(std::vector<std::string> t) {
		text = t;
	}
	void setPlayerProgress(std::shared_ptr<PlayerProgress> p) {
		progress = p;
	}

	unsigned int getId() {
		return id;
	}

	bool condition() {
		return true;
	};

	std::vector<std::string> getText() {
		// TODO conditional advice
		// IE : "you might have luck north of the valley after asking a series of times
		return text;
	}
};

class FlightLeader : public NPCLeader {
private:
	std::shared_ptr<PlayerProgress> progress;
	std::vector<std::string> text;
	unsigned int id = 0;
public:
	FlightLeader() {};
	FlightLeader(std::shared_ptr<PlayerProgress> progress, std::vector<std::string> text, unsigned int id) :progress(progress), text(text), id(id) {};

	void setText(std::vector<std::string> t) {
		text = t;
	}
	void setPlayerProgress(std::shared_ptr<PlayerProgress> p) {
		progress = p;
	}

	unsigned int getId() {
		return id;
	}

	bool condition() {
		if (progress->flightLeaderCarKeys) {
			if (progress->pocketAnimalsFought > 10) {
				return true;
			}
		}
		return false;
	};

	std::vector<std::string> getText() {
		// TODO conditional advice
		// IE : "you might have luck north of the valley after asking a series of times
		return text;
	}
};


class WaterLeader : public NPCLeader{
	private:
		std::shared_ptr<PlayerProgress> progress;
		std::vector<std::string> text;
		unsigned int id = 0;
	public:
		WaterLeader() {};
		WaterLeader(std::shared_ptr<PlayerProgress> progress, std::vector<std::string> text, unsigned int id) :progress(progress), text(text), id(id) {};

		void setText(std::vector<std::string> t) {
			text = t;
		}
		void setPlayerProgress(std::shared_ptr<PlayerProgress> p) {
			progress = p;
		}

		unsigned int getId() {
			return id;
		}

		bool condition() {
			if (progress->waterLeaderBottle) {
				if (progress->pocketAnimalsFought > 4) {
					return true;
				}
			}
			return false;
		};

		std::vector<std::string> getText() {
			// TODO conditional advice
			// IE : "you might have luck north of the valley after asking a series of times
			return text;
		}
};


class NPCTracker {
private:
	std::unordered_map<unsigned int, NPCLeader*> npcs;
public:

	NPCTracker(std::vector<NPCLeader*> npcLeaders) {
		for (auto leader : npcLeaders) {
			npcs.insert({ leader->getId(), leader });
		}
	}
	bool checkId(unsigned int id) {
		return npcs[id]->condition();
	};
	std::vector<std::string> getText(unsigned int id) {
		return npcs[id]->getText();
	}

};