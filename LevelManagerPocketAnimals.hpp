#pragma once
#include "..\SGPE\LevelManager.hpp"
#include "LevelPocketAnimals.hpp"

class LevelManagerPocketAnimals : public LevelManager
{
private:
	std::vector<LevelPocketAnimals*> levels;
	Level* activeLevel;
	int indexLevel;
public:
	LevelManagerPocketAnimals(std::vector<LevelPocketAnimals*> levels) :levels(levels), activeLevel(levels[0]), indexLevel(0) {}
	~LevelManagerPocketAnimals() {};
	void Next()
	{
		int tempIndexLevel = indexLevel;
		int levelCount = levels.size();
		tempIndexLevel++;

		if (tempIndexLevel <= levelCount) {
			indexLevel = indexLevel + 1;
			activeLevel = levels[indexLevel];
		}
	}

	void Previous()
	{
		int tempIndexLevel = indexLevel;
		int levelCount = levels.size();
		tempIndexLevel--;

		if (tempIndexLevel > 0) {
			indexLevel = indexLevel - 1;
			activeLevel = levels[indexLevel];
		}

	}
	void resetStart()
	{
		indexLevel = 0;
		activeLevel = levels[indexLevel];
	}


	void Start() {
		activeLevel->Start();
	}
	void Update() {

		activeLevel->Update();
	}

	void Render() {
		activeLevel->Render();
	}

	//should be called upon destruction of a class or its instance, stored here due to not having a good location in mind a.t.m.

	template<typename T>
	void destroy_vector(std::vector<T*> &v) {
		while (!v.empty()) {
			delete v.back();
			v.pop_back();
		}
	}

};

