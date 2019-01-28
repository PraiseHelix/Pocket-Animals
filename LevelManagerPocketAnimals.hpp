#pragma once
#include "..\SGPE\LevelManager.hpp"
#include "..\SGPE\Level.hpp"
#include "LevelManagerPocketAnimalsSync.hpp"

class LevelManagerPocketAnimals : public LevelManager
{
private:
	std::vector<Level*> levels;
	Level* activeLevel;
	int indexLevel;
	std::shared_ptr<LevelManagerPocketAnimalsSync> levelController;
	bool loop = true;


public:
	LevelManagerPocketAnimals(std::vector<Level*> levels, std::shared_ptr<LevelManagerPocketAnimalsSync> levelController) 
		:levels(levels), activeLevel(levels[0]), indexLevel(0), levelController(levelController){}
	~LevelManagerPocketAnimals() {};
	void Next()
	{	
		std::cout << "next" << std::endl;
		int tempIndexLevel = indexLevel;
		int levelCount = levels.size();
		tempIndexLevel++;
		if (tempIndexLevel <= levelCount) {
			indexLevel = indexLevel + 1;
			activeLevel = levels[indexLevel];
		}
	}
	void Skip(int i) {
		

	}

	void Previous()
	{
		std::cout << "previous" << std::endl;
		int tempIndexLevel = indexLevel;
		int levelCount = levels.size();
		tempIndexLevel--;

		if (tempIndexLevel > 0) {
			indexLevel = indexLevel - 1;
			activeLevel = levels[indexLevel];
		}

	}
	void ResetStart()
	{
		std::cout << "restart" << std::endl;
		indexLevel = 0;
		activeLevel = levels[indexLevel];
	}
	void Start() {
		activeLevel->Start();
	}
	void Update() {
		while (loop) {
			if (!levelController->getSet()) {
				activeLevel->Update();
				activeLevel->Render();
			}else {
				int caseInt = levelController->getOrderType();
				switch (caseInt) {
					std::cout << "new order" << std::endl;
					case 1:
						ResetStart();
						break;
					case 2:
						Previous();
						break;
					case 3:
						Next();
						break;
					case 4:
						loop = false;
						break;
					default:
						Skip(caseInt);
						break;
				}
			}
		}

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

