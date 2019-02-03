#pragma once
#include "..\SGPE\LevelManager.hpp"
#include "..\SGPE\Level.hpp"
#include "LevelManagerPocketAnimalsSync.hpp"
#include <stdlib.h> 


// TODO start function
class LevelManagerPocketAnimals : public LevelManager
{
private:
	std::vector<Level*> levels;
	Level* activeLevel;
	int indexLevel;
	std::shared_ptr<LevelManagerPocketAnimalsSync> levelController;
	bool loop = true;


public:
	LevelManagerPocketAnimals(std::vector<Level*> levels, std::shared_ptr<LevelManagerPocketAnimalsSync> levelController, unsigned int start = 0)
		:levels(levels), activeLevel(levels[start]), indexLevel(start), levelController(levelController){}
	~LevelManagerPocketAnimals() {};

	/// \brief
	/// Switching the activeLevel pointer up
	void Next()
	{	
		int tempIndexLevel = indexLevel;
		int levelCount = levels.size();
		tempIndexLevel++;
		if (tempIndexLevel <= levelCount) {
			indexLevel = indexLevel + 1;
			activeLevel = levels[indexLevel];
		}
		Start();
	}

	/// \brief
	/// Not implemented.
	void Skip(int i) {
		// TODO: Allow skipping multiple levels
	}

	/// \brief
	/// Switching the activeLevel pointer down
	void Previous()
	{
		int tempIndexLevel = indexLevel;
		int levelCount = levels.size();
		tempIndexLevel--;

		if (tempIndexLevel > 0) {
			indexLevel = indexLevel - 1;
			activeLevel = levels[indexLevel];
		}
		Start();
	}

	/// \brief
	/// Switching the activeLevel to the begin
	void ResetStart()
	{
		indexLevel = 0;
		activeLevel = levels[indexLevel];
	}

	/// \brief
	/// Upon switching calling the start method of a level
	void Start() {
		activeLevel->Start();
	}

	/// \brief
	/// update method that's continously run during execution time
	void Update() {
			if (!activeLevel->ownTimeManager) {
				sf::Time t= sf::milliseconds(100);
				sf::sleep(t);
			}
			if (!levelController->getSet()) {
				activeLevel->Update();
				activeLevel->Render();
			}else {

				int caseInt = levelController->getOrderType();
				switch (caseInt) {
					// TODO: Better to make it a enum class and select future positions
					case 1:
						ResetStart();
						break;
					case 2:
						Previous();
						break;
					case 3:
						Next();
						break;
				}
			}	
	}

	/// \brief
	/// Calling the level to render

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

