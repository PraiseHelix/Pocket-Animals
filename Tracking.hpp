#pragma once
#include <memory>
#include <unordered_map>

class PlayerProgress{
public:
	bool waterLeaderBottle = false;
	bool landLeaderSwitchBlade = false;
	bool flightLeaderCarKeys = false;
	bool phsyicLeaderSpoon = false;
	int pocketAnimalsFought = 0;
};


class NPC {
private:
	std::vector<std::string> text;
public:
	NPC() {};
	NPC(std::vector<std::string> text) :text(text) {}
	virtual std::vector<std::string> getText() = 0;

};


class NPCLeader {
private:
public:
	NPCLeader() {};
	virtual bool condition() = 0;
	virtual std::vector<std::string> getText() = 0;
};


class WaterLeader {
	private:
		std::shared_ptr<PlayerProgress> progress;
		std::vector<std::string> text;
	public:
		WaterLeader() {};
		WaterLeader(std::shared_ptr<PlayerProgress> progress, std::vector<std::string> text) :progress(progress), text(text) {};
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
		
	}
	bool checkId(unsigned int id) {
		return npcs[id]->condition();
	};
	std::vector<std::string> getText(unsigned int id) {
		return npcs[id]->getText();
	}

};