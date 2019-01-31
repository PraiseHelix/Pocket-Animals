#pragma once
#include <memory>
#include <unordered_map>

class PlayerProgress{
public:

public:
	bool waterLeaderBottle = false;
	bool landLeaderSwitchBlade = false;
	bool flightLeaderCarKeys = false;
	bool phsyicLeaderSpoon = false;
	int pocketAnimalsFought = 0;
};



class NPCLeader {
private:
public:
	NPCLeader() {};
	virtual bool condition() = 0;
	virtual std::vector<std::string> getText() = 0;
	virtual unsigned int getId() = 0;
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