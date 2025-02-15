#pragma once
#include "scene.h"
#include <graphics.h>

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;
extern Scene* rank_scene;
extern Scene* wait_scene;
extern Scene* repos_scene;
class SceneManager {

public:
	enum class SceneType
	{
		Menu,
		Game,
		WAIT,
		Selector,
		Rank,
		Repos
	};

	SceneManager() =default;
	~SceneManager() = default;

	void set_current_scene(Scene* scene) {
		current_scene = scene;
		current_scene->on_enter();
	}

	void switch_to(SceneType type) {
		current_scene->exit();
		switch (type)
		{
		case SceneManager::SceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneManager::SceneType::Game:
			current_scene = game_scene;
			break;
		case SceneManager::SceneType::Selector:
			current_scene = selector_scene;
			break;
		case SceneManager::SceneType::Rank:
			current_scene = rank_scene;
			break;
		case SceneManager::SceneType::WAIT:
			current_scene = wait_scene;
			break;
		case SceneManager::SceneType::Repos:
			current_scene = repos_scene;
			break;
		default:
			break;
		}
		current_scene->on_enter();
	}

	void on_input(const ExMessage &msg) {
		current_scene->on_input(msg);
	}

	void on_update(int delta) {
		current_scene->on_update(delta);
	}

	void on_draw(const Camera& camera) {
		current_scene->on_draw(camera);
	}


private:
	Scene* current_scene;
};