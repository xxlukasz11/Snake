#include <allegro5/allegro_font.h>
#include <fstream>
#include "gameOverState.h"

constexpr const char* HIGHSCORES_FILE_NAME = "snake_results.dat";

namespace {

int getHighestScoreSoFar() {
	std::fstream file(HIGHSCORES_FILE_NAME, std::ios::in);
	int maxValue = 0;
	for (int result; file >> result;) {
		if (result > maxValue) {
			maxValue = result;
		}
	}
	file.close();
	return maxValue;
}

void saveResult(int snakeSize) {
	std::fstream file(HIGHSCORES_FILE_NAME, std::ios::app);
	file << " " << snakeSize;
	file.close();
}

} // namespace

GameOverState::GameOverState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine),
		appContext(appContext),
		gameContext(gameContext) {
}

void GameOverState::onEnter() {
	appContext.stopFrameRateUpdates();
	handleGameEnd();
}

void GameOverState::handleStateEvent(const ALLEGRO_EVENT& event) {
	if (event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_Y) {
		handleYesResponse();
		return;
	}
	if (event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_N) {
		handleNoResponse();
		return;
	}
}

void GameOverState::handleGameEnd() {
	const auto& snakeContext = gameContext.getSnakeContext();
	auto snakeSize = snakeContext.getSnakeSize();
	auto highestScore = getHighestScoreSoFar();
	saveResult(snakeSize);
	drawEndingScreen(snakeSize, highestScore);
}

void GameOverState::drawEndingScreen(int snakeSize, int highestScore) const {
	const auto& snakeContext = gameContext.getSnakeContext();
	const auto& worldMap = gameContext.getWorldMap();
	auto font = appContext.getMainFont();
	const auto& display = appContext.getDisplay();
	worldMap.drawMap();
	worldMap.drawSnake(snakeContext);
	if (snakeSize == highestScore) {
		al_draw_text(font, al_map_rgb(0, 0, 0), display.width / 2, display.height / 4, ALLEGRO_ALIGN_CENTRE,
				"EXCELLENT! YOU MATCHED THE RECORD!");
	} else if (snakeSize > highestScore) {
		al_draw_text(font, al_map_rgb(0, 0, 0), display.width / 2, display.height / 4, ALLEGRO_ALIGN_CENTRE,
				"EXCELLENT! THAT IS HIGHEST SCORE!");
	} else {
		al_draw_text(font, al_map_rgb(0, 0, 0), display.width / 2, display.height / 4, ALLEGRO_ALIGN_CENTRE,
				"GAME OVER");
	}

	al_draw_textf(font, al_map_rgb(0, 0, 0), display.width / 2, display.height / 4 + 50, ALLEGRO_ALIGN_CENTRE,
			"Snake length: %d", snakeSize);
	if (snakeSize < highestScore) {
		al_draw_textf(font, al_map_rgb(0, 0, 0), display.width / 2, display.height / 4 + 85, ALLEGRO_ALIGN_CENTRE,
				"Current highsore: %d", highestScore);
	} else if (snakeSize > highestScore) {
		al_draw_textf(font, al_map_rgb(0, 0, 0), display.width / 2, display.height / 4 + 85, ALLEGRO_ALIGN_CENTRE,
				"Previous highscore: %d", highestScore);
	}

	al_draw_text(font, al_map_rgb(0, 0, 0), display.width / 2, display.height / 4 + 120, ALLEGRO_ALIGN_CENTRE,
			"Play again? [y/n]");

	worldMap.flushDisplay();
}

void GameOverState::handleYesResponse() {
	// TODO introduce new state - RESTART
}

void GameOverState::handleNoResponse() {
	appContext.stopApp();
}
